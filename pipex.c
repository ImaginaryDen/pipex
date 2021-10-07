#include "pipex.h"

int	files_open(char *file_1, char *file_2, int *fd_1, int *fd_2)
{
	*fd_1 = open(file_1, O_RDONLY);
	*fd_2 = open(file_2, O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (*fd_1 == -1)
	{
		perror(file_1);
		return (-1);
	}
	if (*fd_2 == -1)
	{
		perror(file_2);
		return (-1);
	}
	return (0);
}

int init_cmds(t_pipe_data *cmd, int size, char **argv, char **envp)
{
	int i;

	i = 0;
	while (i < size)
	{
		if (ft_init_cmd_data(cmd + i, argv[i + 2], envp))
		{
			ft_putstr_fd(PROGRAM_NAME, 2);
			ft_putstr_fd(": command not found: ", 2);
			ft_putstr_fd(argv[i + 2], 2);
			ft_putstr_fd("\n", 2);
		}
		i++;
	}
	return (0);
}

int *insert_pipe(t_pipe_data *cmds, int size, int file_in, int file_out)
{
	int	*end;
	int	i;

	i = 0;
	end = malloc(sizeof(int) * (size - 1) * 2);
	if (!end)
		return (NULL);
	while (i < size - 1)
	{
		if (pipe(end + i * 2))
		{
			free(end);
			return (NULL);
		}
		cmds[i].fd_in_out[1] = end[i * 2 + 1];
		cmds[i + 1].fd_in_out[0] = end[i * 2];
		i++;
	}
	cmds[0].fd_in_out[0] = file_in;
	cmds[size - 1].fd_in_out[1] = file_out;
	return (end);
}

int  run_cmds(t_pipe_data *cmds, int *end, int size)
{
	int		i;
	int		pid;
	pid_t	*pid_cmd;
	int		status;

	pid_cmd = malloc(sizeof(pid_t) * size);
	i = 0;
	while (i < size)
	{
		pid = fork();
		if (pid == -1)
		{
			free(pid_cmd);
			perror("fork");
			return (1);
		}
		if (!pid)
		{
			close(end[i]);
			ft_cmd(cmds + i);
			return (1);
		}
		pid_cmd[i] = pid;
		i++;
	}
	i = 0;
	while (i < (size - 1) * 2)
	{
		close(end[i]);
		i++;
	}
	i = 0;
	while (i < size)
	{
		waitpid(pid_cmd[i], &status, 0);
		i++;
	}
	free(pid_cmd);
	return (0);
}

void free_cmds(t_pipe_data *cmds, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free_cmd(cmds + i);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	*cmds;
	int			file_in;
	int			file_out;
	int			status;
	int			*end;

	if (files_open(argv[1], argv[argc - 1], &file_in, &file_out))
		return (1);
	cmds = malloc(sizeof(t_pipe_data) * (argc - 3));
	init_cmds(cmds, argc - 3, argv, envp); 
	end = insert_pipe(cmds, argc - 3, file_in, file_out);
	if (end == NULL)
		return (1);
	if (run_cmds(cmds, end, argc - 3) == 1)
		return (0);
	close(file_out);
	close(file_in);
	free(end);
	free_cmds(cmds, argc - 3);
	free(cmds);
	return (0);
}

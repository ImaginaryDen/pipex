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

int init_cmds(t_pipe_data *cmd_1, t_pipe_data *cmd_2, char **argv, char **envp) // переписать для бонуса
{
	if (ft_init_cmd_data(cmd_1, argv[2], envp))
	{
		ft_putstr_fd(PROGRAM_NAME, 2);
		ft_putstr_fd(": command not found: ", 2);
		ft_putstr_fd(argv[2], 2);
		ft_putstr_fd("\n", 2);
	}
	if (ft_init_cmd_data(cmd_2, argv[3], envp))
	{
		ft_putstr_fd(PROGRAM_NAME, 2);
		ft_putstr_fd(": command not found: ", 2);;
		ft_putstr_fd(argv[3], 2);
		ft_putstr_fd("\n", 2);
	}	
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	cmds[2];
	int			file_in;
	int			file_out;
	pid_t		brench_1;
	pid_t		brench_2;
	int			end[2];
	int			status;

	if (argc != 5 || files_open(argv[1], argv[4], &file_in, &file_out)
		|| pipe(end))
		return (1);
	init_cmds(&cmds[0], &cmds[1], argv, envp);
	cmds[0].fd_in_out[0] = file_in;
	cmds[0].fd_in_out[1] = end[1];
	cmds[1].fd_in_out[0] = end[0];
	cmds[1].fd_in_out[1] = file_out;
	brench_2 = fork();
	if (!brench_2)
	{
		close(end[1]);
		ft_cmd(&cmds[1]);
		return (0);
	}
	brench_1 = fork();
	if (!brench_1)
	{
		close(end[0]);
		ft_cmd(&cmds[0]);
		return (0);
	}
	close(end[1]);
	close(end[0]);
	close(file_out);
	close(file_in);
	waitpid(brench_1, &status, 0);
	waitpid(brench_2, &status, 0);
	free_cmd(&cmds[1]);
	free_cmd(&cmds[0]);
	return (0);
}
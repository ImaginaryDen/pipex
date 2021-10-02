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

int init_cmds(t_pipe_data *cmd_1, t_pipe_data *cmd_2, char **argv, char **envp)
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
	t_pipe_data cmd_1;
	t_pipe_data cmd_2;
	int file_in;
	int file_out;
	int	brench;
	int end[2];

	if (argc != 5)
		return (0);

	init_cmds(&cmd_1, &cmd_2, argv, envp);
	if (files_open(argv[1], argv[4], &file_in, &file_out))
		return (1);
	pipe(end);
	cmd_1.fd_in_out[0] = file_in;
	cmd_1.fd_in_out[1] = end[1];
	cmd_2.fd_in_out[0] = end[0];
	cmd_2.fd_in_out[1] = file_out;
	brench = fork();
	if (brench)
	{
		close(end[0]);
		ft_cmd(&cmd_1);
		return (0);
	}
	brench = fork();
	if (brench)
	{
		close(end[1]);
		ft_cmd(&cmd_2);
		return (0);
	}
	close(end[1]);
	close(end[0]);
	close(file_out);
	close(file_in);
	return (0);
}
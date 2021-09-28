#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data cmd_1;
	int file_in;
	int file_out;

	file_in = open(argv[1], O_RDONLY);
	file_out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	ft_init_cmd_data(&cmd_1, argv[2], envp);
	cmd_1.fd_in_out[0] = file_in;
	cmd_1.fd_in_out[1] = file_out;
	ft_cmd(&cmd_1);
}
#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int end[2];
	int fd_1;
	int	fd_2;
	int br_1;
	int br_2;
	int	status;

	fd_1 = open(argv[1], O_RDONLY);
	fd_2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, , 0644);

	pipe(end);
	br_1 = fork();	
	if (br_1)
	{
		close(end[0]);
		ft_cmd(fd_1, argv[2], end[1], envp);
		close(end[1]);
		return (0);
	}
	br_2 = fork();
	if (br_2)
	{
		close(end[1]);
		ft_cmd(end[0], argv[3], fd_2, envp);
		close(end[0]);
		return (0);
	}
	close(end[0]);
	close(end[1]);
	close(fd_1);
	close(fd_2);
	waitpid(br_1, &status, 0);
	waitpid(br_2, &status, 0);
}
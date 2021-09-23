#include "pipex.h"

int in_cmd(char *file, char **cmd, int fd_out)
{
	printf("work 1\n");
	write(fd_out, "Hello !!\n", 11);
	printf("work 1 end\n");
	return (0);
}

int out_cmd(char *file, char **cmd, int fd_in)
{
	char str[100];
	int i;

	i = 0;
	printf("work 2\n");
	while(read(fd_in, str + i, 1) > 0 && str[i])
		i++;
	printf("mg - %s", str);
	printf("work 2 end\n");
	return (0);
}

int	main(int argc, char **argv)
{
	int	end[2];
	int	status;
	pid_t child_1;
	pid_t child_2;

	pipe(end);
	child_1 = fork();
	if (child_1 < 0)
		perror("Fork :");
	else if (child_1 == 0)
	{
		return (in_cmd(NULL, NULL, end[1]));
	}
	child_2 = fork();
	if (child_2 < 0)
		perror("Fork :");
	else if (child_2 == 0)
	{
		return(out_cmd(NULL, NULL, end[0]));
	}
	close(end[0]);
	close(end[1]);
	waitpid(child_1, &status, 0);
	waitpid(child_2, &status, 0);
}
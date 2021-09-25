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

int	main(int argc, char **argv, char **envp)
{
	// char **arg = ft_split("/bin/ls .", ' ');

	// execve(arg[0], arg , envp);
	ft_cmd(0, "ldsfs .", 0, envp);
}
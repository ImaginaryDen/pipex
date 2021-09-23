#include "pipex.h"

int cmd(int fd_in, char *cmd, int fd_out)
{
	char *str;

	str = malloc(100);
	while(read(fd_in, str + i, 1) > 0 && str[i])
		i++;
	return (1);
}
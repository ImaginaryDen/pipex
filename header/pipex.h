#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_pipe_data
{
	int		fd_in_out[2];
	char	**cmd_ard;
}	t_pipe_data;


int		ft_cmd(int fd_in, char *cmd, int fd_out, char **envp);
char	*ft_read_fd(int fd);
void	ft_free_dable_arr(char **strs);
char	*ft_get_path(char *path, char *cmd)

#endif
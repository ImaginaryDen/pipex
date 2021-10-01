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

# define PROGRAM_NAME pipex

typedef struct s_pipe_data
{
	int		fd_in_out[2];
	char	**cmd_ard;
	char	**env;
}	t_pipe_data;


int		ft_cmd(t_pipe_data *data);
char	*ft_read_fd(int fd);
void	ft_free_dable_arr(char **strs);
int		ft_init_cmd_data(t_pipe_data *data, char *argv, char **env);

#endif
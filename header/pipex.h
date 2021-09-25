#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

int		ft_cmd(int fd_in, char *cmd, int fd_out, char **envp);
char	*ft_read_fd(int fd);
void	ft_free_dable_arr(char **strs);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:26:23 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/09 20:05:41 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <errno.h>

# define PROGRAM_NAME "pipex"
# define READ_FD 0
# define WRITE_FD 1

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
void	free_cmd(t_pipe_data *data);
void	ft_wait_all_pid(pid_t *pid_cmd, int size);
int		ft_run_cmds(t_pipe_data *cmds, int *end, int size);
int		ft_run_fork(int i, int *end, t_pipe_data *cmds, int size);
void	ft_close_pipe(int i, int *end, int size);
void	ft_free_cmds(t_pipe_data *cmds, int size);
char	*get_next_line(int fd);
void	ft_print_error(char *str, char *name);

#endif
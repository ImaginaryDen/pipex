/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_for_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:36:43 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/12 19:58:11 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_run_cmds(t_pipe_data *cmds, int *end, int size, int pid)
{
	int		i;
	pid_t	*pid_cmd;

	pid_cmd = malloc(sizeof(pid_t) * size);
	if (!pid_cmd)
		return (0);
	i = 0;
	while (i < size)
	{
		pid_cmd[i] = fork();
		if (pid_cmd[i] == -1)
		{
			free(pid_cmd);
			perror("fork");
			return (1);
		}
		if (!pid_cmd[i])
			return (ft_run_fork(i, end, cmds));
		ft_close_pipe(i, end);
		i++;
	}
	ft_wait_all_pid(pid_cmd, size, pid);
	free(pid_cmd);
	return (0);
}

int	ft_run_fork(int i, int *end, t_pipe_data *cmds)
{
	close(end[(i + 1) * 2]);
	close(end[(i + 1) * 2 - 1]);
	if (cmds[i].fd_in_out[READ_FD] != -1 && cmds[i].fd_in_out[WRITE_FD] != -1)
		ft_cmd(cmds + i);
	return (1);
}

void	ft_close_pipe(int i, int *end)
{
	if (i)
	{
		close(end[(i + 1) * 2 - 1]);
		close(end[(i + 1) * 2 - 2]);
	}
}

void	ft_free_all(t_pipe_data **cmds, int size)
{
	int	i;

	i = 0;
	while (*cmds + i && i < size)
	{
		free_cmd(*cmds + i);
		i++;
	}
	free(*cmds);
	*cmds = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_for_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:36:43 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/14 17:00:16 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	get_fork(t_pipe_data *cmd, pid_t *pid, int i)
{
	pid[i] = -2;
	if (!access(cmd->cmd_ard[0], X_OK)
		&& cmd->fd_in_out[READ_FD] != -1 && cmd->fd_in_out[WRITE_FD] != -1)
		pid[i] = fork();
	if (pid[i] == -1)
	{
		perror("fork");
		return (-1);
	}
	return (0);
}

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
		if (get_fork(cmds + i, pid_cmd, i))
			break ;
		if (!pid_cmd[i])
			ft_run_fork(i, end, cmds, size);
		ft_close_pipe(i, end);
		i++;
	}
	ft_wait_all_pid(pid_cmd, size, pid);
	free(pid_cmd);
	return (0);
}

void	ft_run_fork(int i, int *end, t_pipe_data *cmds, int size)
{
	if (i + 1 < size && end[(i + 1) * 2] != -1)
		close(end[(i + 1) * 2]);
	if (end[(i + 1) * 2 - 1] != -1)
		close(end[(i + 1) * 2 - 1]);
	ft_cmd(cmds, i);
	exit(EXIT_SUCCESS);
}

void	ft_close_pipe(int i, int *end)
{
	if (i)
	{
		close(end[(i + 1) * 2 - 1]);
		close(end[(i + 1) * 2 - 2]);
	}
}

void	ft_free_all(t_pipe_data **cmds, int size, int *end)
{
	int	i;

	i = 0;
	while (*cmds + i && i < size)
	{
		free_cmd(*cmds + i);
		i++;
	}
	free(*cmds);
	free(end);
	*cmds = NULL;
}

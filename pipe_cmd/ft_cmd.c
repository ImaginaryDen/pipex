/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:27:05 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/11 20:55:52 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_cmd(t_pipe_data *data)
{
	int		ret;

	dup2(data->fd_in_out[READ_FD], STDIN_FILENO);
	dup2(data->fd_in_out[WRITE_FD], STDOUT_FILENO);
	ret = 0;
	if (data->cmd_ard != NULL)
		ret = execve(data->cmd_ard[0], data->cmd_ard, data->env);
	close(data->fd_in_out[READ_FD]);
	close(data->fd_in_out[WRITE_FD]);
	return (ret);
}

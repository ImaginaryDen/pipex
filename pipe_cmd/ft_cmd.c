/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:27:05 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/09 17:27:06 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_cmd(t_pipe_data *data)
{
	int		ret;
	char	*cmd_p;

	dup2(data->fd_in_out[READ_FD], STDIN_FILENO);
	dup2(data->fd_in_out[WRITE_FD], STDOUT_FILENO);
	ret = 0;
	if (data->cmd_ard != NULL)
		ret = execve(data->cmd_ard[0], data->cmd_ard, data->env);
	close(data->fd_in_out[0]);
	close(data->fd_in_out[1]);
	return (ret);
}

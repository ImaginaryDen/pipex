/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:27:05 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/13 19:51:07 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_cmd(t_pipe_data *data, int i)
{
	int		ret;

	dup2(data[i].fd_in_out[READ_FD], STDIN_FILENO);
	dup2(data[i].fd_in_out[WRITE_FD], STDOUT_FILENO);
	ret = 0;
	errno = 0;
	if (data[i].cmd_ard != NULL)
		ret = execve(data[i].cmd_ard[0], data[i].cmd_ard, data[i].env);
	return (ret);
}

void	free_cmd(t_pipe_data *data)
{
	if (data->cmd_ard)
	{
		ft_free_dable_arr(data->cmd_ard);
		data->cmd_ard = NULL;
	}
}

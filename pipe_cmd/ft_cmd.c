/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:27:05 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/12 23:10:54 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_cmd(t_pipe_data *data, int *end, int i, int size)
{
	int		ret;

	//data[i].cmd_ard[0][0] = 'a';
	// ft_putstr_fd(data[i].cmd_ard[0], 1);
	// ft_putstr_fd("\n", 1);
	dup2(data[i].fd_in_out[READ_FD], STDIN_FILENO);
	dup2(data[i].fd_in_out[WRITE_FD], STDOUT_FILENO);
	ret = 0;
	if (data[i].cmd_ard != NULL)
		ret = execve(data[i].cmd_ard[0], data[i].cmd_ard, data[i].env);
	//ft_free_all(&data, size, end);
	//errno = 0;
	return (ret);
	//close(data[i].fd_in_out[READ_FD]);
	//close(data[i].fd_in_out[WRITE_FD]);
}

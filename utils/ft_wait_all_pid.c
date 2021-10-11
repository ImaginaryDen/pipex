/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_all_pid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:27:56 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/11 21:58:06 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_wait_all_pid(pid_t *pid_cmd, int size, int pid)
{
	int	i;
	int	status;	

	i = 0;
	waitpid(pid, &status, 0);
	while (i < size)
	{
		waitpid(pid_cmd[i], &status, 0);
		i++;
	}
}

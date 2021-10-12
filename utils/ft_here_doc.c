/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:01:28 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/12 20:01:34 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	here_doc_gnl(int *end, char *limit)
{
	char		*str;
	const int	len = ft_strlen(limit);

	close(end[0]);
	str = get_next_line(0);
	while (str)
	{
		if (!ft_strncmp(str, limit, len) && str[len] == '\n')
			break ;
		write(end[1], str, ft_strlen(str));
		free(str);
		str = get_next_line(0);
	}
	if (str)
		free(str);
	close(end[1]);
	exit(0);
}

int	here_doc(char *limit, int *end, char *file_2, int *fd_2)
{
	pid_t		pid;

	*fd_2 = open(file_2, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd_2 == -1)
		perror(file_2);
	pipe(end);
	pid = fork();
	if (!pid)
		here_doc_gnl(end, limit);
	close(end[1]);
	return (pid);
}

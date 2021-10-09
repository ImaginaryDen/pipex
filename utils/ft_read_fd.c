/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:27:50 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/09 17:27:51 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_read_fd(int fd)
{
	int		i;
	int		buf;
	char	*str;

	i = 1;
	str = NULL;
	while (read(fd, &buf, 1) > 0 && buf)
	{
		str = ft_realoc_str(str, i + 1);
		str[i - 1] = buf;
		str[i] = 0;
		i++;
	}
	return (str);
}

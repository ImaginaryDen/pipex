/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:57:10 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/09 20:04:49 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_print_error(char *str, char *name)
{
	ft_putstr_fd(PROGRAM_NAME, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(name, 2);
	ft_putstr_fd("\n", 2);
}

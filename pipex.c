/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:28:06 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/09 17:36:26 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	files_open(char *file_1, char *file_2, int *fd_1, int *fd_2)
{
	*fd_1 = open(file_1, O_RDONLY);
	*fd_2 = open(file_2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_1 == -1)
	{
		perror(file_1);
		return (-1);
	}
	if (*fd_2 == -1)
	{
		perror(file_2);
		return (-1);
	}
	return (0);
}

int	init_cmds(t_pipe_data *cmd, int size, char **argv, char **envp)
{
	int	i;
	int	ret;

	i = 0;
	while (i < size)
	{
		ret = ft_init_cmd_data(cmd + i, argv[i + 2], envp);
		if (ret == -1)
		{
			ft_putstr_fd(PROGRAM_NAME, 2);
			ft_putstr_fd(": command not found: ", 2);
			ft_putstr_fd(argv[i + 2], 2);
			ft_putstr_fd("\n", 2);
		}
		else if (ret == 2)
		{
			ft_putstr_fd(PROGRAM_NAME, 2);
			ft_putstr_fd(": permission denied: ", 2);
			ft_putstr_fd(argv[i + 2], 2);
			ft_putstr_fd("\n", 2);
		}
		i++;
	}
	return (0);
}

int	*insert_pipe(t_pipe_data *cmds, int size, int file_in, int file_out)
{
	int	*end;
	int	i;

	i = 0;
	end = malloc(sizeof(int) * (size - 1) * 2);
	if (!end)
		return (NULL);
	while (i < size - 1)
	{
		if (pipe(end + i * 2))
		{
			free(end);
			return (NULL);
		}
		cmds[i + 1].fd_in_out[READ_FD] = end[i * 2 + READ_FD];
		cmds[i].fd_in_out[WRITE_FD] = end[i * 2 + WRITE_FD];
		i++;
	}
	cmds[0].fd_in_out[READ_FD] = file_in;
	cmds[size - 1].fd_in_out[WRITE_FD] = file_out;
	return (end);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	*cmds;
	int			file_in;
	int			file_out;
	int			status;
	int			*end;

	if (argc != 5)
		return (1);
	files_open(argv[1], argv[argc - 1], &file_in, &file_out);
	cmds = malloc(sizeof(t_pipe_data) * (argc - 3));
	init_cmds(cmds, argc - 3, argv, envp);
	end = insert_pipe(cmds, argc - 3, file_in, file_out);
	if (end == NULL)
		return (1);
	if (ft_run_cmds(cmds, end, argc - 3) == 1)
		return (0);
	close(file_out);
	close(file_in);
	free(end);
	ft_free_cmds(cmds, argc - 3);
	free(cmds);
	return (0);
}

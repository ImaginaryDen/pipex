/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:28:06 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/13 19:17:56 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	files_open(char *file_1, char *file_2, int *fd)
{
	int	ret;

	fd[0] = open(file_1, O_RDONLY);
	fd[1] = -1;
	fd[2] = open(file_2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	ret = 0;
	if (fd[0] == -1)
	{
		perror(file_1);
		ret = -1;
	}
	if (fd[2] == -1)
	{
		perror(file_2);
		ret = -1;
	}
	return (ret);
}

t_pipe_data	*init_cmds(int size, char **argv, char **envp)
{
	int			i;
	int			ret;
	t_pipe_data	*cmd;

	i = 0;
	cmd = malloc(sizeof(t_pipe_data) * size);
	if (!cmd)
		return (NULL);
	while (i < size)
	{
		ret = ft_init_cmd_data(cmd + i, argv[i + 2], envp);
		if (ret == -1)
			return (NULL);
		else if (ret == 1)
			ft_print_error(": command not found: ", argv[i + 2]);
		else if (ret == 2)
			ft_print_error(": permission denied: ", argv[i + 2]);
		i++;
	}
	return (cmd);
}

int	*insert_pipe(t_pipe_data *cmds, int size, int *fd)
{
	int	*end;
	int	i;

	i = 0;
	end = malloc(sizeof(int) * (size + 1) * 2);
	if (!end)
		return (NULL);
	while (i < size - 1)
	{
		if (pipe(end + (i + 1) * 2))
		{
			free(end);
			return (NULL);
		}
		cmds[i + 1].fd_in_out[READ_FD] = end[(i + 1) * 2 + READ_FD];
		cmds[i].fd_in_out[WRITE_FD] = end[(i + 1) * 2 + WRITE_FD];
		i++;
	}
	end[0] = fd[0];
	end[1] = fd[1];
	cmds[0].fd_in_out[READ_FD] = fd[0];
	cmds[size - 1].fd_in_out[WRITE_FD] = fd[2];
	return (end);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	*cmds;
	int			file[3];
	int			*end;
	int			flag;
	int			pid;

	if (argc < 5)
		return (1);
	flag = 0;
	if (ft_strncmp(argv[1], "here_doc", 9))
		files_open(argv[1], argv[argc - 1], file);
	else
	{
		flag = 1;
		pid = here_doc(argv[2], file, argv[argc - 1]);
	}
	pid = 0;
	cmds = init_cmds((argc - 3 - flag), argv + flag, envp);
	end = insert_pipe(cmds, (argc - 3 - flag), file);
	if (cmds && end && ft_run_cmds(cmds, end, (argc - 3 - flag), pid) == 1)
		return (0);
	close(file[2]);
	close(file[0]);
	ft_free_all(&cmds, (argc - 3 - flag), end);
	return (0);
}

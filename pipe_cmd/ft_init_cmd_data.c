/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmd_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:27:07 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/09 20:12:32 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_full_path(char *path, char *cmd)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	result = ft_strjoin(temp, cmd);
	free(temp);
	return (result);
}

char	**ft_get_paths(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	return (ft_split(envp[i] + 5, ':'));
}

char	*check_cmd(t_pipe_data *data)
{
	int		i;
	char	**paths;
	char	*path_cmd;

	paths = ft_get_paths(data->env);
	i = 0;
	while (paths[i])
	{
		path_cmd = ft_full_path(paths[i], data->cmd_ard[0]);
		if (!access(path_cmd, X_OK))
			break ;
		free(path_cmd);
		path_cmd = NULL;
		i++;
	}
	ft_free_dable_arr(paths);
	return (path_cmd);
}

int	ft_init_cmd_data(t_pipe_data *data, char *argv, char **env)
{
	char	*path_cmd;

	data->env = env;
	data->cmd_ard = ft_split(argv, ' ');
	if (data->cmd_ard == NULL)
		return (-1);
	if (!access(data->cmd_ard[0], X_OK)
		&& (data->cmd_ard[0][0] == '.' || data->cmd_ard[0][0] == '/'))
		return (0);
	if (access(data->cmd_ard[0], X_OK)
		&& (data->cmd_ard[0][0] == '.' || data->cmd_ard[0][0] == '/'))
		return (1);
	if (!access(data->cmd_ard[0], F_OK)
		&& (data->cmd_ard[0][0] == '.' || data->cmd_ard[0][0] == '/'))
		return (2);
	path_cmd = check_cmd(data);
	if (path_cmd == NULL)
		return (1);
	free(data->cmd_ard[0]);
	data->cmd_ard[0] = path_cmd;
	return (0);
}

void	free_cmd(t_pipe_data *data)
{
	if (data->cmd_ard)
	{
		ft_free_dable_arr(data->cmd_ard);
		data->cmd_ard = NULL;
	}
}

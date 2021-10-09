#include "pipex.h"

char *ft_full_path(char *path, char *cmd)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	result = ft_strjoin(temp, cmd);
	free(temp);
	return (result);
}

char **ft_get_paths(char **envp)
{
	int i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	return (ft_split(envp[i] + 5, ':'));
}

char *check_cmd(t_pipe_data *data)
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
			break;
		free(path_cmd);
		path_cmd = NULL;
		i++;
	}
	ft_free_dable_arr(paths);
	return (path_cmd);
}

int ft_init_cmd_data(t_pipe_data *data, char *argv, char **env)
{
	char *path_cmd;
	int i;

	data->env = env;
	data->cmd_ard = ft_split(argv, ' ');
	if (!access(data->cmd_ard[0], X_OK))
		return (0);
	if (!access(data->cmd_ard[0], F_OK))
		return (2);
	path_cmd = check_cmd(data);
	if (path_cmd == NULL)
	{
		free_cmd(data);
		return (-1);
	}
	free(data->cmd_ard[0]);
	data->cmd_ard[0] = path_cmd;
	return (0);
}

void free_cmd(t_pipe_data *data)
{
	if (data->cmd_ard)
	{
		ft_free_dable_arr(data->cmd_ard);
		data->cmd_ard = NULL;
	}
}
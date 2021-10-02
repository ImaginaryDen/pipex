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

int ft_init_cmd_data(t_pipe_data *data, char *argv, char **env)
{
	char **paths;
	char *path_cmd;
	int i;

	data->env = env;
	data->cmd_ard = ft_split(argv, ' ');
	paths = ft_get_paths(data->env);
	i = -1;
	while (paths[++i])
	{
		path_cmd = ft_full_path(paths[i], data->cmd_ard[0]);
		if (!access(path_cmd, 1))
			break;
		free(path_cmd);
		path_cmd = NULL;
	}
	ft_free_dable_arr(paths);
	if (path_cmd == NULL)
	{
		ft_free_dable_arr(data->cmd_ard);
		data->cmd_ard = NULL;
		return (-1);
	}
	free(data->cmd_ard[0]);
	data->cmd_ard[0] = path_cmd;
	return (0);
}
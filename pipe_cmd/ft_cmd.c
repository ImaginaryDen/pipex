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

char *ft_get_path(char **envp)
{
	int i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	return (ft_split(envp[i] + 5, ':'));
}

int	ft_cmd(t_pipe_data *data)
{
	int		i;
	char	*cmd_p;

	str = NULL;
	dup2(data->fd_in_out[1], STDIN_FILENO);
	dup2(data->fd_in_out[2], STDOUT_FILENO);
	cmd_arg = ft_split(data->cmd, ' ');
	i = 0;
	while (paths && paths[i])
	{
		cmd_p = ft_get_path(paths[i], cmd_arg[0]);
		if (!access(cmd_p, 1))
			break;
		free(cmd_p);
		cmd_p = NULL;
		i++;
	}
	free(cmd_arg[0]);
	if (cmd_p)
		cmd_arg[0] = cmd_p;
	if (execve(cmd_arg[0], cmd_arg, envp) == -1)
	{
		ft_putstr_fd("command not found: ", 1);
		ft_putstr_fd(cmd_arg[0], 1);
		ft_putstr_fd("\n", 1);
	}
	close(fd_in);
	close(fd_out);
	if (cmd_p)
		free(cmd_p);
	if (str)
		free(str);
	ft_free_dable_arr(paths);
	return (1);
}
#include "pipex.h"

char *ft_get_path(char *path, char *cmd)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	result = ft_strjoin(temp, cmd);
	free(temp);
	return (result);
}

int get_nbr_path(char **envp)
{
	int i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	return (i);
}

int	ft_cmd(int fd_in, char *cmd, int fd_out, char **envp)
{
	int		i;
	char	*cmd_p;
	char	*str;
	char	**paths;
	char	**cmd_arg;

	str = NULL;
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	paths = ft_split(envp[get_nbr_path(envp)] + 5, ':');
	cmd_arg = ft_split(cmd, ' ');
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
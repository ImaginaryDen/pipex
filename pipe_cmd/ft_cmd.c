#include "pipex.h"

int	ft_cmd(t_pipe_data *data)
{
	int		ret;
	char	*cmd_p;

	dup2(data->fd_in_out[0], STDIN_FILENO);
	dup2(data->fd_in_out[1], STDOUT_FILENO);
	ret = execve(data->cmd_ard[0], data->cmd_ard, data->env);
	close(data->fd_in_out[0]);
	close(data->fd_in_out[1]);
	return (ret);
}
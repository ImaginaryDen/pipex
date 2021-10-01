#include "pipex.h"

int	ft_cmd(t_pipe_data *data)
{
	int		i;
	char	*cmd_p;

	dup2(data->fd_in_out[0], STDIN_FILENO);
	dup2(data->fd_in_out[1], STDOUT_FILENO);
	if (execve(data->cmd_ard[0], data->cmd_ard, data->env) == -1)
		return (-1);
	close(data->fd_in_out[0]);
	close(data->fd_in_out[1]);
	return (0);
}
#include "pipex.h"

void	ft_free_dable_arr(char **strs)
{
	int i;

	while (strs && strs + i && strs[i])
	{
		free(strs[i]);
		i++;
	}
	if (strs)
		free(strs);
}

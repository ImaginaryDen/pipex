#include "pipex.h"

char	*ft_read_fd(int fd)
{
	int		i;
	int		buf;
	char	*str;

	i = 1;
	str = NULL;
	while(read(fd, &buf, 1) > 0 && buf)
	{
		str = ft_realoc_str(str, i + 1);
		str[i - 1] = buf;
		str[i] = 0;
		i++;
	}
	return (str);
}

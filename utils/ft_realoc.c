#include <stdlib.h>

char *ft_realoc_str(char *old, int size)
{
	char *new_ptr;
	int				i;

	new_ptr = malloc(size);
	i = 0;
	while (old && old[i] && i < size)
	{
		new_ptr[i] = old_ptr[i];
		i++;
	}
	new_ptr[i] = 0;
	return (new_ptr);
}
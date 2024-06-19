#include "cub3d.h"

char	*gnl_skip_nl(int fd)
{
	char	*str;

	str = get_next_line(fd);
	while (str && !ft_strcmp(str, "\n"))
	{
		free(str);
		str = get_next_line(fd);
	}
	return (str);
}
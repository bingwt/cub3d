#include "cub3d.h"

static char	**get_map(int fd)
{
	char	*lines;
	char	*next_line;
	char	**content;

	content = NULL;
	lines = NULL;
	str = gnl_skip_nl(fd);
	while (str)
	{
		if (!lines)
			lines = ft_strdup(str);
		else
			lines = ft_strjoin_free(lines, str, lines)
		free(str);
		str = get_next_line(fd);
		if (!ft_strcmp(str, "\n"))
		{
			free(str);
			str = gnl_skip_nl(fd);
			if (str)
			{
				free(str);
				free(lines);
				printf("Error\nEmpty line found in map content\n");
				return (NULL);
			}
		}
	}
	content = ft_split(lines, '\n');
	free(lines);
	return (content);
}

t_map	set_map(t_map map, int fd)
{
	char	**content;
	
	content = get_map(fd);
}
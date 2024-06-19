#include "cub3d.h"

static void	replace_spaces(char **str)
{
	int	i = 0;

	while ((*str)[i])
	{
		if ((*str)[i] == ' ')
			(*str)[i] = '0';
		i++;
	}
}

static char	*map_loop(char *str, int fd)
{
	char	*lines;

	lines = NULL;
	while (str)
	{
		if (!lines)
			lines = ft_strdup(str);
		else
			lines = ft_strjoin_free(lines, str, lines);
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
	return (lines);
}

static char	**get_map(int fd)
{
	char	*str;
	char	*lines;
	char	**content;

	content = NULL;
	lines = NULL;
	str = gnl_skip_nl(fd);
	lines = map_loop(str, fd);
	if (lines)
	{
		content = ft_split(lines, '\n');
		free(lines);
	}
	return (content);
}

t_map	set_map(t_map map, int fd)
{
	int		i;
	char	**content;
	
	i = -1;
	content = get_map(fd);
	while (content[++i])
		replace_spaces(&content[i]);
	if (!valid_map(content))
	{
		ft_free_split(&content);
		return (map);
	}
	content = normalise_map(content);
	map.width = longest_width(content);
	map.height = ft_squarelen(content);
	map.matrix = convert_map(content);
	ft_free_split(&content);
	return (map);
}
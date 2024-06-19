#include "cub3d.h"

int		longest_width(char **content)
{
	int	i;
	int	current;
	int	longest;

	i = 0;
	longest = 0;
	while (content[i])
	{
		current = ft_strlen(content[i]);
		if (current > longest)
			longest = current;
		i++;
	}
	return (longest);
}

static char	*inject_padding(char *line, int width)
{
	int		i;
	int		line_len;
	char	*padded;

	i = -1;
	line_len = ft_strlen(line);
	padded = ft_calloc(1, width + 1);
	while (++i < line_len)
		padded[i] = line[i];
	while (i < width)
	{
		padded[i] = '0';
		i++;
	}
	return (padded);
}

char	**normalise_map(char **content)
{
	int		i;
	int		height;
	int		width;
	char	**squared;

	i = -1;
	width = longest_width(content);
	height = ft_squarelen(content);
	squared = ft_calloc(sizeof(char *), height + 1);
	while (++i < height)
		squared[i] = inject_padding(content[i], width);
	ft_free_split(&content);
	return (squared);
}
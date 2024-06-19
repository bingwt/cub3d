#include "cub3d.h"

static int	player_orientation(char c)
{
	if (c == 'N')
		return (360);
	else if (c == 'S')
		return (180);
	else if (c == 'E')
		return (90);
	else
		return (270);
}

int	**convert_map(char **content)
{
	int	i;
	int	j;
	int	*line;
	int	**map;

	i = 0;
	j = 0;
	map = ft_calloc(sizeof(int *), ft_squarelen(content));
	while (content[i])
	{
		line = ft_calloc(sizeof(int), ft_strlen(content[i]));
		while (content[i][j])
		{
			if (content[i][j] == '0')
				line[j] = 0;
			else if (content[i][j] == '1')
				line[j] = 1;
			else
				line[j] = player_orientation(content[i][j]);
			j++;
		}
		j = 0;
		map[i] = line;
		i++;
	}
	return (map);
}
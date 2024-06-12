#include "cub3d.h"

static bool	valid_lines(char ***lines)
{
	int	i;
	int	mask;

	i = 0;
	mask = 0;
	while (i < 6)
	{
		if (!ends_with_xpm(lines[i][1]))
			return (false);
		else if (!ft_strcmp(lines[i][0], "NO"))
			mask |= NO_MASK;
		else if (!ft_strcmp(lines[i][0], "SO"))
			mask |= SO_MASK;
		else if (!ft_strcmp(lines[i][0], "EA"))
			mask |= EA_MASK;
		else if (!ft_strcmp(lines[i][0], "WE"))
			mask |= WE_MASK;
		else
			return (false);
		i++;
	}
	if (mask == ALL_MASK)
		return (true);
	return (false);
}

static char	***verify_scene(char **scene)
{
	int		i;
	char	***lines;

	i = 0;
	if (!scene)
		return (NULL);
	lines = ft_calloc(sizeof(char **) * 7);
	if (!lines)
		return (NULL);
	while (i < 6)
		lines[i] = ft_split(scene[i++], ' ');
	if (!valid_lines(lines))
	{
		ft_free_cubed(&lines);
		return (NULL);
	}
	while (--i >= 0)
		if (ft_squarelen(lines[i]) != 2)
			{
				printf("Error\nScene description has extra elements");
				ft_free_cubed(&lines);
				return (NULL);
			}
	return (lines);
}

static char	**get_scene(int fd)
{
	int		i;
	char	*str;
	char	**scene;

	i = 0;
	scene = ft_calloc(sizeof(char *) * 7);
	if (!scene)
		return (NULL);
	while (i < 6)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		else if (!ft_strcmp(str, "\n"))
		{
			free(str);
			continue ;
		}
		scene[i++] = str;
	}
	if (i == 6)
		return (scene);
	ft_free_split(&scene);
	return (NULL);
}

t_map	set_scene(int fd)
{
	char	**scene;
	char	***lines;
	t_map	map;

	map.no = NULL;
	scene = get_scene(fd);
	lines = verify_scene(scene);
	ft_free_split(&scene);
	if (!lines || !valid_rgbs(lines))
		return (map);
	assign_textures(&map, lines);
	assign_rgbs(&map, lines);
	ft_free_cubed(&lines);
	return (map);
}
#include "cub3d.h"

static int	mask_check(int mask, char *identifier)
{
	if (!ft_strcmp(identifier, "NO"))
		mask |= NO_MASK;
	else if (!ft_strcmp(identifier, "SO"))
		mask |= SO_MASK;
	else if (!ft_strcmp(identifier, "EA"))
		mask |= EA_MASK;
	else if (!ft_strcmp(identifier, "WE"))
		mask |= WE_MASK;
	else if (!ft_strcmp(identifier, "F"))
		mask |= F_MASK;
	else if (!ft_strcmp(identifier, "C"))
		mask |= C_MASK;
	else
		mask = -1;
	return (mask);
}

static bool	valid_lines(char ***lines)
{
	int	i;
	int	mask;

	i = 0;
	mask = 0;
	while (i < 6)
	{
		if (ft_strcmp(lines[i][0], "C") && ft_strcmp(lines[i][0], "F")
			&& !ends_with_xpm(lines[i][1]))
			return (false);
		mask = mask_check(mask, lines[i][0]);
		if (mask == -1)
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

	i = -1;
	if (!scene)
		return (NULL);
	lines = ft_calloc(sizeof(char **), 7);
	if (!lines)
		return (NULL);
	while (++i < 6)
		lines[i] = ft_split(scene[i], ' ');
	while (--i >= 0)
		if (ft_squarelen(lines[i]) != 2)
			{
				printf("Error\nScene description has extra or missing elements\n");
				ft_free_cubed(&lines);
				return (NULL);
			}
	if (!valid_lines(lines))
	{
		printf("Error\nScene description format is incorrect\n");
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
	scene = ft_calloc(sizeof(char *), 7);
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
		str[ft_strlen(str) - 1] = '\0';
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:45:57 by xlow              #+#    #+#             */
/*   Updated: 2024/08/01 02:48:18 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_door(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'D')
		{
			map->has_door = 1;
			map->dr = "maps/textures/door.xpm";
			if (!check_perms(map->dr))
			{
				printf("Error\nCheck that door texture is valid\n");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

static bool	char_check(char *next, char *line)
{
	int			i;
	static int	j;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != 'D' && line[i] != 'C')
		{
			printf("Error\nIncorrect character found in map content\n");
			return (false);
		}
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			j++;
	}
	if (!next && j != 1)
	{
		printf("Error\nIncorrect player spawns allocated\n");
		return (false);
	}
	return (true);
}

static void	flood_fill(char **error, char **content, int x, int y)
{
	if (*error)
		return ;
	if (x < 0 || y < 0 || !content[y] || !content[y][x])
	{
		*error = "Error\nPlayer is not correctly surrounded by walls\n";
		printf("%s", *error);
		content = NULL;
		return ;
	}
	if (content[y][x] == '1' || content[y][x] == '2')
		return ;
	content[y][x] = '2';
	flood_fill(error, content, x + 1, y);
	flood_fill(error, content, x - 1, y);
	flood_fill(error, content, x, y + 1);
	flood_fill(error, content, x, y - 1);
}

static bool	check_boundaries(char **content)
{
	int		x;
	int		y;
	char	*error;
	char	**copy;

	x = -1;
	y = 0;
	error = NULL;
	while (content[y])
	{
		while (content[y][++x])
			if (content[y][x] != '0' && content[y][x] != '1')
				break ;
		if (content[y][x] && content[y][x] != '0' && content[y][x] != '1')
			break ;
		x = 0;
		y++;
	}
	copy = ft_splitdup(content);
	flood_fill(&error, copy, x, y);
	ft_free_split(&copy);
	if (error)
		return (false);
	return (true);
}

bool	valid_map(t_map *map, char **content)
{
	int	i;

	i = -1;
	map->has_door = 0;
	while (content[++i])
	{
		if (!char_check(content[i + 1], content[i])
			|| !check_door(map, content[i]))
			return (false);
	}
	if (!check_boundaries(content))
		return (false);
	return (true);
}

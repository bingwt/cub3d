/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:45:57 by xlow              #+#    #+#             */
/*   Updated: 2024/07/17 19:47:47 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	char_check(char *next, char *line)
{
	int			i;
	static int	j = 0;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
		{
			printf("Error\nIncorrect character found in map content\n");
			return (false);
		}
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			j++;
		i++;
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

bool	valid_map(char **content)
{
	int	i;

	i = -1;
	while (content[++i])
		if (!char_check(content[i + 1], content[i]))
			return (false);
	if (!check_boundaries(content))
		return (false);
	return (true);
}

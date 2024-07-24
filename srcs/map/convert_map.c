/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:43:15 by xlow              #+#    #+#             */
/*   Updated: 2024/07/17 19:44:01 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	map_char_to_int(char c)
{
	if (c == '0')
		return (0);
	else if (c == '1')
		return (1);
	else if (c == 'D')
		return (2);
	else
		return (player_orientation(c));
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
			line[j] = map_char_to_int(content[i][j]);
			j++;
		}
		j = 0;
		map[i++] = line;
	}
	return (map);
}

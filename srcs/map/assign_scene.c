/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:05:52 by xlow              #+#    #+#             */
/*   Updated: 2024/06/14 18:06:18 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_textures(t_map *map, char ***lines)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(lines[i][0], "NO"))
			map->no = ft_strdup(lines[i][1]);
		else if (!ft_strcmp(lines[i][0], "SO"))
			map->so = ft_strdup(lines[i][1]);
		else if (!ft_strcmp(lines[i][0], "EA"))
			map->ea = ft_strdup(lines[i][1]);
		else if (!ft_strcmp(lines[i][0], "WE"))
			map->we = ft_strdup(lines[i][1]);
		i++;
	}
}

void	assign_rgbs(t_map *map, char ***lines)
{
	int		i;
	char	**rgb;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(lines[i][0], "F"))
		{
			rgb = ft_split(lines[i][1], ',');
			map->floor.red = ft_atoi(rgb[0]);
			map->floor.green = ft_atoi(rgb[1]);
			map->floor.blue = ft_atoi(rgb[2]);
		}
		else if (!ft_strcmp(lines[i][0], "C"))
		{
			rgb = ft_split(lines[i][1], ',');
			map->ceiling.red = ft_atoi(rgb[0]);
			map->ceiling.green = ft_atoi(rgb[1]);
			map->ceiling.blue = ft_atoi(rgb[2]);
		}
		i++;
	}
}

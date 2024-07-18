/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:16:02 by btan              #+#    #+#             */
/*   Updated: 2024/07/18 15:39:35 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_map *map, t_props *props)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->matrix[y][x] > 1)
			{
				props->player.pos.chunk.x = x;
				props->player.pos.chunk.y = y;
				printf(YELLOW "P" RESET);
			}
			else if (map->matrix[y][x])
				printf(CYAN "%d" RESET, map->matrix[y][x]);
			else
				printf(BLACK "%d" RESET, map->matrix[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

int	goto_cell(t_vec2 cell, t_props *props)
{
	int	x;
	int	y;

	x = props->player.pos.chunk.x;
	y = props->player.pos.chunk.y;
	if (!props->map.matrix[(int) cell.y][(int) cell.x])
	{
		props->map.matrix[(int) cell.y][(int) cell.x] = props->map.matrix[y][x];
		props->map.matrix[y][x] = 0;
		return (0);
	}
	return (1);
}

int	fill_front(t_props *props)
{
	int	x;
	int	y;

	x = props->player.pos.chunk.x;
	y = props->player.pos.chunk.y - 1;
	if (!props->map.matrix[y][x])
	{
		props->map.matrix[y][x] = 1;
		return (0);
	}
	return (1);
}

int	cell_action(t_action action, t_props *props)
{
	t_vec2	dir;

	dir.x = (int) props->player.pos.exact.x;
	dir.y = (int) props->player.pos.exact.y;
	if (props->player.angle >= 315 || props->player.angle < 45)
		dir.y = (int) props->player.pos.exact.y - 1;
	else if (props->player.angle >= 45 && props->player.angle < 135)
		dir.x = (int) props->player.pos.exact.x + 1;
	else if (props->player.angle >= 135 && props->player.angle < 225)
		dir.y = (int) props->player.pos.exact.y + 1;
	else
		dir.x = props->player.pos.chunk.x - 1;
	if (((int) dir.x - 1 < 0 || (int) dir.x + 1 > props->map.width) || \
			((int) dir.y - 1 < 0 || (int) dir.y + 1 > props->map.height))
		return (1);
	if (props->map.matrix[(int) dir.y][(int) dir.x] != (int) action)
	{
		props->map.matrix[(int) dir.y][(int) dir.x] = action;
		return (0);
	}
	return (1);
}

int	check_chunk(t_vec2 pos, t_props *props)
{
	int			**map;

	map = props->map.matrix;
	if ((int) pos.x < 0 || (int) pos.x > props->map.width - 1)
		return (WALL);
	if ((int) pos.y < 0 || (int) pos.y > props->map.height - 1)
		return (WALL);
	return (map[(int) pos.y][(int) pos.x]);
}

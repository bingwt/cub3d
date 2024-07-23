/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:16:02 by btan              #+#    #+#             */
/*   Updated: 2024/07/24 05:16:27 by btan             ###   ########.fr       */
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
			if (map->matrix[y][x] > 2)
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

void	set_interact_pos(t_vec2 *dir, t_props *props)
{
	dir->x = (int) props->player.pos.exact.x;
	dir->y = (int) props->player.pos.exact.y;
	if (props->player.angle >= 315 || props->player.angle < 45)
		dir->y = (int) props->player.pos.exact.y - 1;
	else if (props->player.angle >= 45 && props->player.angle < 135)
		dir->x = (int) props->player.pos.exact.x + 1;
	else if (props->player.angle >= 135 && props->player.angle < 225)
		dir->y = (int) props->player.pos.exact.y + 1;
	else
		dir->x = props->player.pos.exact.x - 1;
}

void	interact(t_action action, t_props *props)
{
	t_vec2	dir;

	set_interact_pos(&dir, props);
	if (((int) dir.x - 1 < 0 || (int) dir.x + 1 > props->map.width) || \
			((int) dir.y - 1 < 0 || (int) dir.y + 1 > props->map.height))
		return ;
	if (action == PLACE && props->map.has_door)
	{
		if (props->map.matrix[(int) dir.y][(int) dir.x] != props->player.hand)
			props->map.matrix[(int) dir.y][(int) dir.x] = props->player.hand;
	}
	else if (action == INTERACT)
	{
		if (abs(props->map.matrix[(int) dir.y][(int) dir.x]) == 2)
			props->map.matrix[(int) dir.y][(int) dir.x] = \
			-props->map.matrix[(int) dir.y][(int) dir.x];
	}
	else if (action == CLEAR)
		props->map.matrix[(int) dir.y][(int) dir.x] = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 17:16:02 by btan              #+#    #+#             */
/*   Updated: 2024/06/25 21:31:01 by btan             ###   ########.fr       */
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
				props->player.position.cell.x = x;
				props->player.position.cell.y = y;
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
	printf("Player @ cell[x: %d][y: %d]\n", (int) props->player.position.cell.x, (int) props->player.position.cell.y);
	printf("Player @ rela[x: %f][y: %f]\n\n", props->player.position.relative.x, props->player.position.relative.y);
}

int	goto_cell(t_vec2 cell, t_props *props)
{
	int	x;
	int	y;

	x = props->player.position.cell.x;
	y = props->player.position.cell.y;
	if (!props->map.matrix[(int) cell.y][(int) cell.x])
	{
		props->map.matrix[(int) cell.y][(int) cell.x] = 270;
		props->map.matrix[y][x] = 0;
		return (0);
	}
	return (1);
}

int	fill_front(t_props *props)
{
	int	x;
	int	y;

	x = props->player.position.cell.x;
	y = props->player.position.cell.y - 1;
	if (!props->map.matrix[y][x])
	{
		props->map.matrix[y][x] = 1;
		return (0);
	}
	return (1);
}

int	cell_action(t_action action, t_props *props)
{
	int	x;
	int	y;

	x = props->player.position.cell.x;
	y = props->player.position.cell.y - 1;
	if (props->map.matrix[y][x] != (int) action)
	{
		props->map.matrix[y][x] = action;
		return (0);
	}
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 00:04:46 by btan              #+#    #+#             */
/*   Updated: 2024/07/15 01:14:42 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_mapbox(t_props *props)
{
	t_vec2	start;
	t_vec2	end;

	start.x = 0;
	end.x = WIDTH / 8;
	start.y = 0;
	end.y = HEIGHT / 8;
	while (start.y < end.y)
	{
		start.x = 0;
		while (start.x < end.x)
		{
			if (start.y == 0 || start.y == end.y - 1 || \
			start.x == 0 || start.x == end.x - 1)
				color_pixel(start.x, start.y, hex_to_dec("ffffff"), props);
			start.x++;
		}
		start.y++;
	}
}

void	draw_player(int size, int color, t_props *props)
{
	t_vec2	player;

	player.x = WIDTH / 16;
	player.y = HEIGHT / 16;
	color_pixel(player.x, player.y, hex_to_dec("ffffff"), props);
	fill_point(player, size, color, props);
}

void	draw_walls(int color, t_props *props)
{
	int		x;
	int		y;
	t_vec2	wall;

	y = 0;
	while (y < props->map.height)
	{
		x = 0;
		while (x < props->map.width)
		{
			if (props->map.matrix[y][x] == 1)
			{
				wall.x = x * 10;
				wall.y = y * 10;
				fill_point(wall, 10, color, props);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_props *props)
{
	draw_mapbox(props);
	draw_player(3, hex_to_dec("ffffff"), props);
	draw_walls(hex_to_dec("ffffff"), props);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:59:41 by btan              #+#    #+#             */
/*   Updated: 2024/06/09 17:30:29 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_point(t_vec2 point, t_props *props)
{
	int		fill;
	t_vec2	end;
	float	start_x;

	fill = 10;
	end.x = point.x + (fill / 2);
	end.y = point.y + (fill / 2);
	start_x = point.x - (fill / 2);
	point.y = point.y - (fill / 2);
	while (point.y++ <= end.y)
	{
		point.x = start_x;
		while (point.x <= end.x)
		{
			draw_pixel(point.x++, point.y, props);
		}
	}
}

void	player(t_props *props)
{
	t_color color;
	t_vec2	pos;

	color.red = 0;
	color.green = 128;
	color.blue = 0;
	props->pixel.color = rgb_to_dec(&color);
	pos.y = 0;
	while (pos.y++ < props->height)
	{
		pos.x = 0;
		if ((pos.x == props->player.pos->x) && (pos.y == props->player.pos->y))
			props->pixel.color = rgb_to_dec(&color);
		while (pos.x < props->width)
		{
			if ((pos.x == props->player.pos->x) && (pos.y == props->player.pos->y))
			{
				draw_pixel(pos.x, pos.y, props);
				fill_point(pos, props);
			}
			pos.x++;
		}
	}
}
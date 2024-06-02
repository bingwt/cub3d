/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 14:59:41 by btan              #+#    #+#             */
/*   Updated: 2024/06/02 17:01:25 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_point(int x, int y, t_props *props)
{
	int	fill;
	int	end_x;
	int	end_y;
	int	start_x;

	fill = 10;
	end_x = x + (fill / 2);
	end_y = y + (fill / 2);
	start_x = x - (fill / 2);
	y = y - (fill / 2);
	while (y++ <= end_y)
	{
		x = start_x;
		while (x <= end_x)
			draw_pixel(x++, y, props);
	}
}

void	player(t_props *props)
{
	t_color color;
	int	x;
	int	y;

	color.red = 0;
	color.green = 128;
	color.blue = 0;
	props->pixel.color = rgb_to_dec(&color);
	y = 0;
	while (y++ < props->height)
	{
		x = 0;
		if ((x == props->player.x) && (y == props->player.y))
			props->pixel.color = rgb_to_dec(&color);
		while (x < props->width)
		{
			if ((x == props->player.x) && (y == props->player.y))
			{
				draw_pixel(x, y, props);
				fill_point(x, y,  props);
			}
			x++;
		}
	}
}

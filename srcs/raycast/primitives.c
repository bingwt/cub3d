/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:18:40 by btan              #+#    #+#             */
/*   Updated: 2024/07/24 05:33:15 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_area(t_vec2 start, t_vec2 end, int color, t_props *props)
{
	int	x;
	int	y;

	y = start.y;
	while (y < end.y)
	{
		x = start.x;
		while (x < end.x)
			color_pixel(x++, y, color, props);
		y++;
	}
}

void	draw_ceiling_floor(t_props *props)
{
	t_vec2	start;
	t_vec2	end;
	int		color;

	start.x = 0;
	end.x = WIDTH;
	start.y = 0;
	end.y = HEIGHT / 2;
	color = rgb_to_dec(&props->map.ceiling);
	fill_area(start, end, color, props);
	start.y = HEIGHT / 2;
	end.y = HEIGHT;
	color = rgb_to_dec(&props->map.floor);
	fill_area(start, end, color, props);
}

void	fill_point(t_vec2 point, int size, int color, t_props *props)
{
	t_vec2	end;
	float	start_x;

	end.x = point.x + (size / 2);
	end.y = point.y + (size / 2);
	start_x = point.x - (size / 2);
	point.y = point.y - (size / 2);
	while (point.y++ <= end.y)
	{
		point.x = start_x;
		while (point.x <= end.x)
			color_pixel(point.x++, point.y, color, props);
	}
}

void	draw_texture(t_vec2 start, int scale, t_img *texture, t_props *props)
{
	t_vec2	pos;
	t_vec2	step;
	int		x;
	int		y;

	pos.x = 0;
	pos.y = 0;
	step.x = texture->width / scale;
	step.y = texture->height / scale;
	y = 0;
	while (y < scale)
	{
		x = 0;
		while (x < scale)
		{
			props->pixel.color = get_pixel_color(texture, pos.x, pos.y);
			if (props->pixel.color != 0)
				draw_pixel(start.x + x, start.y + y, props);
			pos.x += step.x;
			x++;
		}
		pos.x = 0;
		pos.y += step.y;
		y++;
	}
}

void	draw_hotbar(t_props *props)
{
	t_vec2	start;
	int		hand;
	t_img	*hotbar;

	start.x = 0;
	start.y = (HEIGHT / 4) * 3;
	hand = props->player.hand - 1;
	hotbar = &props->hotbar[hand].img;
	draw_texture(start, WIDTH / 4, hotbar, props);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:18:40 by btan              #+#    #+#             */
/*   Updated: 2024/06/24 16:37:59 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

	// for (int y = 0; y < HEIGHT / 2; y++)
	// {
	// 	for (int x = 0; x < HEIGHT; x++)
	// 	{
	// 		color_pixel(x, y, hex_to_dec("ffffff"), &props);
	// 	}
	// }

void fill_area(t_vec2 start, t_vec2 end, int color, t_props *props)
{
    int x;
    int y;

    y = start.y;
    while (y < end.y)
    {
        x = start.x;
        while (x < end.x)
            color_pixel(x++, y, color, props);
        y++;
    }
}

void    draw_ceiling_floor(char type, t_props *props)
{
    t_vec2  start;
    t_vec2  end;
    int     color;

    start.x = 0;
    end.x = WIDTH;
    if (type == 'c')
    {
        start.y = 0;
        end.y = HEIGHT / 2;
        color = rgb_to_dec(&props->map.ceiling);
    }
    else if (type == 'f')
    {
        start.y = HEIGHT / 2;
        end.y = HEIGHT;
        color = rgb_to_dec(&props->map.floor);
    }
    fill_area(start, end, color, props);
}
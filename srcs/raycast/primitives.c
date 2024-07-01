/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitives.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:18:40 by btan              #+#    #+#             */
/*   Updated: 2024/07/01 15:07:45 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void    draw_ceiling_floor(t_props *props)
{
    t_vec2  start;
    t_vec2  end;
    int     color;

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
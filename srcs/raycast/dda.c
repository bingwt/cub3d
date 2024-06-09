/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:13:19 by btan              #+#    #+#             */
/*   Updated: 2024/06/09 15:07:59 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_player(t_vec2 delta, int steps, t_props *props)
{
	float	inc[2];
	float	point[2];
	t_vec2	mouse;
	int		i;

	inc[0] = delta.x / (float) steps;
	inc[1] = delta.y / (float) steps;
	point[0] = props->player.pos.x;
	point[1] = props->player.pos.y;
	mouse.x = props->mouse.x;
	mouse.y = props->mouse.y;
	fill_point(mouse, props);
	i = 0;
	while (i <= steps)
	{
		if (check_cell((int) point[0], (int) point[1], props))
			break ;
		draw_pixel((int) point[0], (int) point[1], props);
		point[0] += inc[0];
		point[1] += inc[1];
		i++;
	}
}

void	draw_dda(t_line *line, t_props *props)
{
	t_color	color;
	t_vec2	delta;
	int		steps;
	int		i;

	color.red = 0;
	color.green = 0;
	color.blue = 128;
	props->pixel.color = rgb_to_dec(&color);
	i = 0;
	while (i < WIDTH)
	{
		delta.x = line->x1 - line->x0 + i;
		delta.y = line->y1 - line->y0;
		steps = fabs(delta.y);
		if (fabs(delta.x) > fabs(delta.y))
			steps = fabs(delta.x);
		dda_player(delta, steps, props);
		i++;
	}
}

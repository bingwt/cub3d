/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:13:19 by btan              #+#    #+#             */
/*   Updated: 2024/06/04 02:15:44 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_player(int dx, int dy, int steps, t_props *props)
{
	float	inc[2];
	float	point[2];
	int		i;

	inc[0] = dx / (float) steps;
	inc[1] = dy / (float) steps;
	point[0] = props->player.x;
	point[1] = props->player.y;
	fill_point(props->mouse.x, props->mouse.y, props);
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
	int		dx;
	int		dy;
	int		steps;

	color.red = 0;
	color.green = 0;
	color.blue = 128;
	props->pixel.color = rgb_to_dec(&color);
	dx = line->x1 - line->x0;
	dy = line->y1 - line->y0;
	steps = abs(dy);
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	dda_player(dx, dy, steps, props);
}

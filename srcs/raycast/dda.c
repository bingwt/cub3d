/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:13:19 by btan              #+#    #+#             */
/*   Updated: 2024/06/04 13:14:51 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_abs(double n)
{
	if (n < 0)
		n = -n;
	return (n);
}

void	dda_player(double dx, double dy, double steps, t_props *props)
{
	double	inc[2];
	double	point[2];
	double		i;

	inc[0] = dx / (double) steps;
	inc[1] = dy / (double) steps;
	point[0] = props->player.x;
	point[1] = props->player.y;
	fill_point(props->mouse.x, props->mouse.y, props);
	i = 0;
	while (i <= steps)
	{
		if (check_cell((double) point[0], (double) point[1], props))
			break ;
		if ((double) point[1] >= HEIGHT)
			return ;
		draw_pixel((double) point[0], (double) point[1], props);
		point[0] += inc[0];
		point[1] += inc[1];
		i++;
	}
}

void	draw_dda(t_line *line, t_props *props)
{
	t_color	color;
	double		dx;
	double		dy;
	double		steps;
	double		i;

	color.red = 0;
	color.green = 0;
	color.blue = 128;
	props->pixel.color = rgb_to_dec(&color);
	i = 64;
	while (i > -64)
	{
		dx = line->x1 - line->x0;
		dy = line->y1 - line->y0 + i;
		steps = ft_abs(dy);
		if (ft_abs(dx) > ft_abs(dy))
			steps = ft_abs(dx);
		dda_player(dx, dy, steps, props);
		i--;
	}
}

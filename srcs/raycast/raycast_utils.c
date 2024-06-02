/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:22:07 by btan              #+#    #+#             */
/*   Updated: 2024/06/02 17:19:06 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	dda_line(int x, int y, t_props *props)
{
	t_color	color;
	int		dx;
	int		dy;
	int		x_inc;
	int		y_inc;
	int		steps;
	int		i;

	color.red = 0;
	color.green = 0;
	color.blue = 128;
	props->pixel.color = rgb_to_dec(&color);
	fill_point(x, y, props);
	dx = x - props->player.x;
	dy = y - props->player.y;
	if (ft_abs(dx) > ft_abs(dy))
		steps = ft_abs(dx);
	else
		steps = ft_abs(dy);
	x_inc = dx / steps;
	y_inc = dy / steps;
	x = props->player.x;
	y = props->player.y;
	i = 1;
	while (i <= steps)
	{
		props->pixel.color = rgb_to_dec(&color);
		draw_pixel(x, y, props);
		x = x + x_inc;
		y = y + y_inc;
		i++;
	}
}

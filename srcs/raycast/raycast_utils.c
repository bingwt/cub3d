/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:22:07 by btan              #+#    #+#             */
/*   Updated: 2024/06/02 17:31:12 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static void	check_slope(int *axis, int *iter)
{
	*iter = -1;
	if (*axis < 0)
		*axis = -(*axis);
	else
		*iter = 1;
}

static void	draw_bresenham_low(t_line *line, t_props *props)
{
	int	dx;
	int	dy;
	int	yi;
	int	diff;
	int	y;

	dx = line->x1 - line->x0;
	dy = line->y1 - line->y0;
	check_slope(&dy, &yi);
	diff = (2 * dy) - dx;
	y = line->y0;
	while (line->x0 <= line->x1)
	{
		draw_pixel(line->x0, y, props);
		if (diff > 0)
		{
			y = y + yi;
			diff = diff - (2 * dx);
		}
		diff = diff + (2 * dy);
		line->x0++;
	}
}

static void	draw_bresenham_high(t_line *line, t_props *props)
{
	int	dx;
	int	dy;
	int	xi;
	int	diff;
	int	x;

	dx = line->x1 - line->x0;
	dy = line->y1 - line->y0;
	check_slope(&dx, &xi);
	diff = 2 * dx - dy;
	x = line->x0;
	while (line->y0 <= line->y1)
	{
		draw_pixel(x, line->y0, props);
		if (diff > 0)
		{
			x = x + xi;
			diff = diff - (2 * dy);
		}
		diff = diff + (2 * dx);
		line->y0++;
	}
}

void	draw_bresenham(t_line *line, t_props *props)
{
	t_color	color;
	int		dx;
	int		dy;

	color.red = 0;
	color.green = 0;
	color.blue = 128;
	props->pixel.color = rgb_to_dec(&color);
	dx = line->x1 - line->x0;
	dy = line->y1 - line->y0;
	fill_point(line->x1, line->y1, props);
	if (ft_abs(dy) < ft_abs(dx))
	{
		if (line->x0 > line->x1)
		{
			ft_swap(&line->x0, &line->x1);
			ft_swap(&line->y0, &line->y1);
		}
		draw_bresenham_low(line, props);
	}
	else
	{
		if (line->y0 > line->y1)
		{
			ft_swap(&line->x0, &line->x1);
			ft_swap(&line->y0, &line->y1);
		}
		draw_bresenham_high(line, props);
	}
}

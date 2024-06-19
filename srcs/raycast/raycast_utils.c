/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:22:07 by btan              #+#    #+#             */
/*   Updated: 2024/06/09 15:11:40 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_slope(float *axis, int *iter)
{
	*iter = -1;
	if (*axis < 0)
		*axis = -(*axis);
	else
		*iter = 1;
}

static void	draw_bresenham_low(t_line *line, t_props *props)
{
	t_vec2	delta;
	int		yi;
	int		diff;
	int		y;

	delta.x = line->x1 - line->x0;
	delta.y = line->y1 - line->y0;
	check_slope(&delta.y, &yi);
	diff = (2 * delta.y) - delta.x;
	y = line->y0;
	while (line->x0 <= line->x1)
	{
		if (check_cell(line->x0, y, props))
			break ;
		draw_pixel(line->x0, y, props);
		if (diff > 0)
		{
			y = y + yi;
			diff = diff - (2 * delta.x);
		}
		diff = diff + (2 * delta.y);
		line->x0++;
	}
}

static void	draw_bresenham_high(t_line *line, t_props *props)
{
	t_vec2	delta;
	int		xi;
	int		diff;
	int		x;

	delta.x = line->x1 - line->x0;
	delta.y = line->y1 - line->y0;
	check_slope(&delta.x, &xi);
	diff = 2 * delta.x - delta.y;
	x = line->x0;
	while (line->y0 <= line->y1)
	{
		if (check_cell(x, line->y0, props))
			break ;
		draw_pixel(x, line->y0, props);
		if (diff > 0)
		{
			x = x + xi;
			diff = diff - (2 * delta.y);
		}
		diff = diff + (2 * delta.x);
		line->y0++;
	}
}

void	draw_bresenham(t_line *line, t_props *props)
{
	t_color	color;
	t_vec2	delta;
	t_vec2	line_end;

	color.red = 0;
	color.green = 0;
	color.blue = 128;
	props->pixel.color = rgb_to_dec(&color);
	delta.x = line->x1 - line->x0;
	delta.y = line->y1 - line->y0;
	line_end.x = line->x1;
	line_end.y = line->y1;
	fill_point(line_end, props);
	if (fabs(delta.y) < fabs(delta.x))
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

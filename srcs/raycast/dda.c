/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:13:19 by btan              #+#    #+#             */
/*   Updated: 2024/06/18 17:41:34 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dda_player(t_vec2 delta, int steps, t_line *intercept, t_props *props)
{
	float	inc[2];
	float	point[2];
	// t_vec2	mouse;
	int		i;

	inc[0] = delta.x / (float) steps;
	inc[1] = delta.y / (float) steps;
	point[0] = props->player.pos->x;
	point[1] = props->player.pos->y;
	// mouse.x = props->mouse.x;
	// mouse.y = props->mouse.y;
	// if (mouse.x > props->mini_width)
	// 	mouse.x = props->mini_width;
	// if (mouse.y > props->mini_height)
	// 	mouse.y = props->mini_height;
	// fill_point(mouse, props);
	i = 0;
	while (i <= steps)
	{
		if (check_cell((int) point[0], (int) point[1], props))
		{
			intercept->x1 = point[0];
			intercept->y1 = point[1];
			return (i);
		}
		draw_pixel((int) point[0], (int) point[1], props);
		point[0] += inc[0];
		point[1] += inc[1];
		i++;
	}
	return (0);
}

void	draw_dda(t_line *line, t_props *props)
{
	t_color	color;
	t_vec2	delta;
	int		steps;

	color.red = 0;
	color.green = 0;
	color.blue = 128;
	props->pixel.color = rgb_to_dec(&color);
	delta.x = line->x1 - line->x0;
	delta.y = line->y1 - line->y0;
	steps = fabs(delta.y);
	if (fabs(delta.x) > fabs(delta.y))
		steps = fabs(delta.x);
	//dda_player(delta, steps, props);
}

float	calc_dist(t_line *line)
{
	float	x;
	float	y;
	float	dist;

	x = line->x1 - line->x0;
	y = line->y1 - line->y0;
	dist = sqrt((x * x) + (y * y));
	return (dist);
}

void	draw_ray(t_line *line, int ray, t_props *props)
{
	t_color	color;
	t_vec2	delta;
	int		steps;
	t_line	*intercept;

	color.red = 0;
	color.green = 0;
	color.blue = 128;
	props->pixel.color = rgb_to_dec(&color);
	delta.x = line->x1 - line->x0;
	delta.y = line->y1 - line->y0;
	steps = fabs(delta.y);
	intercept = ft_calloc(1, sizeof(t_line));
	if (fabs(delta.x) > fabs(delta.y))
		steps = fabs(delta.x);
	if (dda_player(delta, steps, intercept, props))
	{
		printf("x: %f, y: %f\n", line->x1, line->y1);
		intercept->x0 = line->x0;
		intercept->y0 = line->y0;
		printf("dist: %f\n", calc_dist(intercept));
		draw_pixel(ray, HEIGHT / 2, props);
	}
}

void	draw_rays(t_vec2 *player, t_props *props)
{
	t_vec2	*dir;
	t_line	line;
	float	step;
	int		i;

	step = props->player.fov / WIDTH;
	i = 0;
	while (i < WIDTH)
	{
		dir = ft_calloc(1, sizeof(t_vec2));
		dir->y = -1;
		rotate(dir, props->player.angle - (props->player.fov / 2) + (i * step));
		line.x0 = player->x;
		line.y0 = player->y;
		vec2_scale(dir, WIDTH * HEIGHT);
		line.x1 = player->x + dir->x;
		line.y1 = player->y + dir->y;
		draw_ray(&line, i, props);
		free(dir);
		i++;
	}
}

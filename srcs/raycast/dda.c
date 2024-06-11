/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:13:19 by btan              #+#    #+#             */
/*   Updated: 2024/06/11 17:07:16 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_local_origin(t_props *props, t_vec2 *vec2)
{
	int	offset_x;
	int	offset_y;

	offset_x = props->map.cols / 2;
	offset_y = props->map.rows / 2;
	vec2->x -= offset_x;
	vec2->y -= offset_y;
}


void	set_world_origin(t_vec2 *vec2)
{
	int	offset_x;
	int	offset_y;

	offset_x = WIDTH / 2;
	offset_y = HEIGHT / 2;
	vec2->x += offset_x;
	vec2->y += offset_y;
}

void	dda_player(t_vec2 delta, int steps, t_props *props)
{
	float	inc[2];
	float	point[2];
	t_vec2	p;
	t_vec2	mouse;
	int		i;
	t_color	color;

	color.red = 255;
	color.green = 0;
	color.blue = 0;
	inc[0] = delta.x / (float) steps;
	inc[1] = delta.y / (float) steps;
	point[0] = props->player.pos->x;
	point[1] = props->player.pos->y;
	mouse.x = props->mouse.x;
	mouse.y = props->mouse.y;
	fill_point(mouse, props);
	i = 0;
	while (i <= steps)
	{
		if (check_cell((int) point[0], (int) point[1], props))
		{
		//	draw_pixel((int) point[0], (int) point[1], props);
			props->pixel.color = rgb_to_dec(&color);
			p.x = point[0];
			p.y = point[1];
			set_local_origin(props, &p);
			set_world_origin(&p);
			draw_pixel(p.x, p.y, props);
			break ;
		}
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

	color.red = 0;
	color.green = 0;
	color.blue = 128;
	props->pixel.color = rgb_to_dec(&color);
	delta.x = line->x1 - line->x0;
	delta.y = line->y1 - line->y0;
	steps = fabs(delta.y);
	if (fabs(delta.x) > fabs(delta.y))
		steps = fabs(delta.x);
	dda_player(delta, steps, props);
}

void	draw_ray(t_vec2 *player, t_props *props)
{
	t_vec2	*dir;
	t_line	line;
	float	step;
	int		i;

	step = props->player.fov / TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		dir = ft_calloc(1, sizeof(t_vec2));
		dir->y = -1;
		rotate(dir, props->player.angle - (props->player.fov / 2) + (i * step));
		line.x0 = player->x;
		line.y0 = player->y;
		vec2_scale(dir, WIDTH * HEIGHT);
		line.x1 = player->x + dir->x;
		line.y1 = player->y + dir->y;
		draw_dda(&line, props);
		free(dir);
		i++;
	}
}

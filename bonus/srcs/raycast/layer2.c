/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:03:58 by btan              #+#    #+#             */
/*   Updated: 2024/08/02 14:31:22 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	layer2_collision(t_ray *ray, t_props *props, int tmp)
{
	if (ray->map.x < 0 || ray->map.x >= props->map.width)
		return (1);
	if (ray->map.y < 0 || ray->map.y >= props->map.height)
		return (1);
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == 1)
		return (1);
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == 2 && tmp == 2)
		return (2);
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == -2 && tmp == 2)
		return (-2);
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == 3)
		return (3);
	return (0);
}

void	dda_layer2(t_ray *ray, t_props *props, int tmp)
{
	while (ray->hit == 0)
	{
		if (ray->grid.x < ray->grid.y)
		{
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == -2)
		return ;
			ray->grid.x += ray->delta.x;
			ray->map.x += ray->step.x;
			ray->grid_side = 'x';
			if (ray->step.x > 0)
				ray->wall_face = 'W';
			else
				ray->wall_face = 'E';
		}
		else
		{
			ray->grid.y += ray->delta.y;
			ray->map.y += ray->step.y;
			ray->grid_side = 'y';
			if (ray->step.y > 0)
				ray->wall_face = 'S';
			else
				ray->wall_face = 'N';
		}
		ray->hit = layer2_collision(ray, props, tmp);
	}
}

int	layer2_visible(t_ray *ray, t_props *props)
{
	if (ray->wall_face == 'N' \
		&& (props->map.matrix[(int)ray->map.y + 1][(int)ray->map.x] == 0 \
		|| props->map.matrix[(int)ray->map.y + 1][(int)ray->map.x] > 3))
		return (1);
	else if (ray->wall_face == 'S' \
	&& (props->map.matrix[(int)ray->map.y - 1][(int)ray->map.x] == 0 \
	|| props->map.matrix[(int)ray->map.y - 1][(int)ray->map.x] > 3))
		return (1);
	else if (ray->wall_face == 'E' \
	&& (props->map.matrix[(int)ray->map.y][(int)ray->map.x + 1] == 0 \
	|| props->map.matrix[(int)ray->map.y][(int)ray->map.x + 1] > 3))
		return (1);
	else if (ray->wall_face == 'W' \
	&& (props->map.matrix[(int)ray->map.y][(int)ray->map.x - 1] == 0 \
	|| props->map.matrix[(int)ray->map.y][(int)ray->map.x - 1] > 3))
		return (1);
	return (0);
}

void	layer2_cast(t_props *props, int tmp)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < props->width)
	{
		init_ray(&ray, props, x);
		init_dda(&ray, props);
		dda_layer2(&ray, props, tmp);
		get_hit_pos(&ray, props);
		if (abs(ray.hit) == 2 && x == props->width - 1)
			update_re_doors(ray.hit, props);
		if (abs(ray.hit) == 2 && layer2_visible(&ray, props) && tmp == 2)
			texture_wall_slice(&ray, props, x - (props->re_frame * 40), &props->door_tex.img);
		if (ray.hit == 3 && layer2_visible(&ray, props) && tmp ==3)
			texture_wall_slice(&ray, props, x, \
			&props->coin[props->coin_frame].img);
		if (props->animated && ray.hit != 2)
			texture_wall_slice(&ray, props, x, \
			&props->cat[props->animated - 1].img);
		x++;
	}
}

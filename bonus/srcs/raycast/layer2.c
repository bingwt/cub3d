/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:03:58 by btan              #+#    #+#             */
/*   Updated: 2024/08/01 13:57:13 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	layer2_collision(t_ray *ray, t_props *props)
{
	if (ray->map.x < 0 || ray->map.x >= props->map.width)
		return (1);
	if (ray->map.y < 0 || ray->map.y >= props->map.height)
		return (1);
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == 1)
		return (1);
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == 2)
		return (2);
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == 3)
		return (3);
	return (0);
}

void	dda_layer2(t_ray *ray, t_props *props)
{
	while (ray->hit == 0)
	{
		if (ray->grid.x < ray->grid.y)
		{
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
		ray->hit = layer2_collision(ray, props);
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

void	layer2_cast(t_props *props)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < props->width)
	{
		init_ray(&ray, props, x);
		init_dda(&ray, props);
		dda_layer2(&ray, props);
		get_hit_pos(&ray, props);
		if (ray.hit == 2 && layer2_visible(&ray, props))
			texture_wall_slice(&ray, props, x, &props->re_doors[props->re_frame].img);
		if (ray.hit == 3 && layer2_visible(&ray, props))
			texture_wall_slice(&ray, props, x, \
			&props->coin[props->coin_frame].img);
		if (props->animated && ray.hit != 2)
			texture_wall_slice(&ray, props, x, \
			&props->cat[props->animated - 1].img);
		x++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_layer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:35:04 by btan              #+#    #+#             */
/*   Updated: 2024/08/01 16:40:11 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	enemy_collision(t_ray *ray, t_props *props)
{
	if (ray->map.x < 0 || ray->map.x >= props->map.width)
		return (4);
	if (ray->map.y < 0 || ray->map.y >= props->map.height)
		return (4);
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == 1)
		return (4);
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == 2)
		return (1);
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == 3)
		return (4);
	return (0);
}

void	dda_enemy(t_ray *ray, t_props *props)
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
		ray->hit = enemy_collision(ray, props);
	}
}

int	enemy_visible(t_ray *ray, t_props *props)
{
	if (ray->map.x < 0 || ray->map.x >= props->map.width)
		return (0);
	if (ray->map.y < 0 || ray->map.y >= props->map.height)
		return (0);
	if (ray->wall_face == 'N' \
		&& (props->map.matrix[(int)ray->map.y + 1][(int)ray->map.x] == 0 \
		|| props->map.matrix[(int)ray->map.y + 1][(int)ray->map.x] > 4))
		return (1);
	else if (ray->wall_face == 'S' \
	&& (props->map.matrix[(int)ray->map.y - 1][(int)ray->map.x] == 0 \
	|| props->map.matrix[(int)ray->map.y - 1][(int)ray->map.x] > 4))
		return (1);
	else if (ray->wall_face == 'E' \
	&& (props->map.matrix[(int)ray->map.y][(int)ray->map.x + 1] == 0 \
	|| props->map.matrix[(int)ray->map.y][(int)ray->map.x + 1] > 4))
		return (1);
	else if (ray->wall_face == 'W' \
	&& (props->map.matrix[(int)ray->map.y][(int)ray->map.x - 1] == 0 \
	|| props->map.matrix[(int)ray->map.y][(int)ray->map.x - 1] > 4))
		return (1);
	return (0);
}

void	enemy_cast(t_props *props)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < props->width)
	{
		init_ray(&ray, props, x);
		init_dda(&ray, props);
		dda_enemy(&ray, props);
		get_hit_pos(&ray, props);
		if (ray.hit == 4 && enemy_visible(&ray, props))
			texture_wall_slice(&ray, props, x, \
			&props->hud[props->player.status_frame].img);
		if (props->animated && ray.hit != 2)
			texture_wall_slice(&ray, props, x, \
			&props->cat[props->animated - 1].img);
		x++;
	}
}

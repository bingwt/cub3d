/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:29:08 by btan              #+#    #+#             */
/*   Updated: 2024/07/14 19:20:47 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	collision(t_ray *ray, t_props *props)
{
	if (ray->map.x < 0 || ray->map.x >= props->map.width)
		return (1);
	if (ray->map.y < 0 || ray->map.y >= props->map.height)
		return (1);
	if (props->map.matrix[(int)ray->map.y][(int)ray->map.x] == 1)
		return (1);
	return (0);
}

void	init_dda(t_ray *ray, t_props *props)
{
	ray->step.x = 1;
	ray->step.y = 1;
	if (props->player.pos.dir.x < 0)
	{
		ray->step.x = -1;
		ray->grid.x = (props->player.pos.exact.x - ray->map.x) * ray->delta.x;
	}
	else
		ray->grid.x = (ray->map.x + 1 - props->player.pos.exact.x) * \
					ray->delta.x;
	if (props->player.pos.dir.y < 0)
	{
		ray->step.y = -1;
		ray->grid.y = (props->player.pos.exact.y - ray->map.y) * ray->delta.y;
	}
	else
		ray->grid.y = (ray->map.y + 1 - props->player.pos.exact.y) * \
					ray->delta.y;
}

void	dda(t_ray *ray, t_props *props)
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
		if (collision(ray, props))
			ray->hit = 1;
	}
}

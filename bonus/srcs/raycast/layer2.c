/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:03:58 by btan              #+#    #+#             */
/*   Updated: 2024/08/01 04:29:07 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			texture_wall_slice(&ray, props, x, &props->door_tex.img);
		if (ray.hit == 3 && layer2_visible(&ray, props))
			texture_wall_slice(&ray, props, x, \
			&props->coin[props->coin_frame].img);
		if (props->animated && ray.hit != 2)
			texture_wall_slice(&ray, props, x, \
			&props->cat[props->animated - 1].img);
		x++;
	}
}

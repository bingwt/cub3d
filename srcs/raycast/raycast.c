/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:08:12 by btan              #+#    #+#             */
/*   Updated: 2024/07/31 23:19:38 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_ray *ray, t_props *props, int x)
{
	float	camera;
	t_vec2	plane;

	props->player.pos.dir.x = 0;
	props->player.pos.dir.y = -1;
	rotate(&props->player.pos.dir, props->player.angle);
	plane.x = -props->player.pos.dir.y * 0.5;
	plane.y = props->player.pos.dir.x * 0.5;
	camera = 2 * x / (float) props->width - 1;
	props->player.pos.dir.x = props->player.pos.dir.x + plane.x * camera;
	props->player.pos.dir.y = props->player.pos.dir.y + plane.y * camera;
	ray->map.x = (int) props->player.pos.exact.x;
	ray->map.y = (int) props->player.pos.exact.y;
	ray->delta.x = fabs(1 / props->player.pos.dir.x);
	ray->delta.y = fabs(1 / props->player.pos.dir.y);
	ray->hit = 0;
}

int	set_face_width(t_ray *ray, t_props *props)
{
	int	face_width;

	face_width = props->textures[0].img.width;
	if (ray->hit == 2)
		face_width = props->coin[props->coin_frame].img.width;
	else if (ray->wall_face == 'S')
		face_width = props->textures[1].img.width;
	else if (ray->wall_face == 'E')
		face_width = props->textures[2].img.width;
	else if (ray->wall_face == 'W')
		face_width = props->textures[3].img.width;
	return (face_width);
}

void	get_hit_pos(t_ray *ray, t_props *props)
{
	int	face_width;

	face_width = set_face_width(ray, props);
	if (ray->grid_side == 'x')
		ray->wall_dist = (ray->grid.x - ray->delta.x);
	else
		ray->wall_dist = (ray->grid.y - ray->delta.y);
	if (ray->grid_side == 'x')
		ray->hit_pos = props->player.pos.exact.y + ray->wall_dist * \
					props->player.pos.dir.y;
	else
		ray->hit_pos = props->player.pos.exact.x + ray->wall_dist * \
					props->player.pos.dir.x;
	ray->hit_pos -= floor(ray->hit_pos);
	ray->texture_slice = (int)(ray->hit_pos * face_width);
	if (ray->grid_side == 'x' && props->player.pos.dir.x < 0)
		ray->texture_slice = face_width - ray->texture_slice - 1;
	if (ray->grid_side == 'y' && props->player.pos.dir.y > 0)
		ray->texture_slice = face_width - ray->texture_slice - 1;
}

void	cast_rays(t_props *props)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < props->width)
	{
		init_ray(&ray, props, x);
		init_dda(&ray, props);
		dda(&ray, props);
		get_hit_pos(&ray, props);
		if (ray.hit == 2)
			texture_wall_slice(&ray, props, x, &props->coin[props->coin_frame].img);
		else if (ray.wall_face == 'N')
			texture_wall_slice(&ray, props, x, &props->textures[0].img);
		else if (ray.wall_face == 'S')
			texture_wall_slice(&ray, props, x, &props->textures[1].img);
		else if (ray.wall_face == 'E')
			texture_wall_slice(&ray, props, x, &props->textures[2].img);
		else if (ray.wall_face == 'W')
			texture_wall_slice(&ray, props, x, &props->textures[3].img);
		x++;
	}
}

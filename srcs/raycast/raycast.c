/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:08:12 by btan              #+#    #+#             */
/*   Updated: 2024/07/12 18:16:42 by btan             ###   ########.fr       */
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
	ray->map.x = (int)props->player.pos.exact.x;
	ray->map.y = (int)props->player.pos.exact.y;
	ray->delta.x = fabs(1 / props->player.pos.dir.x);
	ray->delta.y = fabs(1 / props->player.pos.dir.y);
	ray->hit = 0;
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
		ray->grid.x = (ray->map.x + 1 - props->player.pos.exact.x) * ray->delta.x;
	if (props->player.pos.dir.y < 0)
	{
		ray->step.y = -1;
		ray->grid.y = (props->player.pos.exact.y - ray->map.y) * ray->delta.y;
	}
	else
		ray->grid.y = (ray->map.y + 1 - props->player.pos.exact.y) * ray->delta.y;
}

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

void	get_hit_pos(t_ray *ray, t_props *props)
{
	int	texture_width;

	if (ray->wall_face == 'N')
		texture_width = props->textures[0].img.width;
	else if (ray->wall_face == 'S')
		texture_width = props->textures[1].img.width;
	else if (ray->wall_face == 'E')
		texture_width = props->textures[2].img.width;
	else if (ray->wall_face == 'W')
		texture_width = props->textures[3].img.width;
	if (ray->grid_side == 'x')
		ray->wall_dist = (ray->grid.x - ray->delta.x);
	else
		ray->wall_dist = (ray->grid.y - ray->delta.y);
	if (ray->grid_side == 'x')
		ray->hit_pos = props->player.pos.exact.y + ray->wall_dist * props->player.pos.dir.y;
	else
		ray->hit_pos = props->player.pos.exact.x + ray->wall_dist * props->player.pos.dir.x;
	ray->hit_pos -= floor(ray->hit_pos);
	ray->texture_slice = (int)(ray->hit_pos * texture_width);
	if (ray->grid_side == 'x' && props->player.pos.dir.x < 0)
		ray->texture_slice = texture_width - ray->texture_slice - 1;
	if (ray->grid_side == 'y' && props->player.pos.dir.y > 0)
		ray->texture_slice = texture_width - ray->texture_slice - 1;
}

void	draw_wall_slice(t_ray *ray, t_props *props, int x)
{
	int		height;
	int		start;
	int		end;
	float	distance_factor;

	height = (int)(props->height / ray->wall_dist);
	start = -height / 2 + props->height / 2;
	if (start < 0)
		start = 0;
	end = height / 2 + props->height / 2;
	if (end >= props->height)
		end = props->height - 1;
	distance_factor = fmin(ray->wall_dist / 10, 1.0);
	props->pixel.color = color_wall(ray->wall_face, distance_factor);
	while (start < end)
	{
		draw_pixel(x, start, props);
		start++;
	}
}

void	texture_wall_slice(t_ray *ray, t_props *props, int x, t_img *texture)
{
	int		height;
	int		start;
	int		end;
	float	distance_factor;
	float	step;
	float	tex_pos;

	height = (int)(props->height / ray->wall_dist);
	start = (-height / 2) + (props->height / 2);
	if (start < 0)
		start = 0;
	end = (height / 2) + (props->height / 2);
	if (end >= props->height)
		end = props->height - 1;
	distance_factor = fmin(ray->wall_dist / 10, 1.0);
	props->pixel.color = color_wall(ray->wall_face, distance_factor);
	step = 1.0 * texture->height / height;
	tex_pos = (start - props->height / 2 + height / 2) * step;
	while (start < end)
	{
		// props->pixel.color = shade_color(get_pixel_color(texture, ray->texture_slice, (int)tex_pos), distance_factor);
		props->pixel.color = get_pixel_color(texture, ray->texture_slice, (int)tex_pos);
		if (props->pixel.color != 0)
			draw_pixel(x, start, props);
		tex_pos += step;
		start++;
	}
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
		// draw_wall_slice(&ray, props, x);
		if (ray.wall_face == 'N')
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
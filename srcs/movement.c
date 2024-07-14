/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:06:28 by btan              #+#    #+#             */
/*   Updated: 2024/07/15 00:15:09 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_collision_x(t_vec2 pos, t_vec2 dir, t_props *props)
{
	float	next_x;

	next_x = pos.x + dir.x;
	if (next_x < 0 || next_x > props->map.width)
		return (1);
	if (props->map.matrix[(int)pos.y][(int)next_x] == 1)
		return (1);
	return (0);
}

int	check_collision_y(t_vec2 pos, t_vec2 dir, t_props *props)
{
	float	next_y;

	next_y = pos.y + dir.y;
	if (next_y < 0 || next_y > props->map.height)
		return (1);
	if (props->map.matrix[(int)next_y][(int)pos.x] == 1)
		return (1);
	return (0);
}

void	check_collision(t_vec2 dir, t_props *props)
{
	if (!check_collision_x(props->player.pos.exact, dir, props))
		props->player.pos.relative.x += dir.x;
	if (!check_collision_y(props->player.pos.exact, dir, props))
		props->player.pos.relative.y += dir.y;
}

void	set_speed(int key, t_props *props)
{
	if (key == 65505)
		props->player.speed += 1;
	else if (key == 65507)
		props->player.speed -= 1;
}

void	handle_movement(int key, t_props *props)
{
	t_vec2	dir;

	dir.x = 0;
	dir.y = 0;
	if (key == 119)
		dir.y = -0.1;
	else if (key == 115)
		dir.y = 0.1;
	else if (key == 97)
		dir.x = -0.1;
	else if (key == 100)
		dir.x = 0.1;
	if (key == 115 || key == 119 || key == 97 || key == 100)
	{
		vec2_scale(&dir, props->player.speed);
		rotate(&dir, props->player.angle);
		check_collision(dir, props);
	}
	else if (key == 65505 || key == 65507)
		set_speed(key, props);
	props->player.pos.exact.x = props->player.pos.chunk.x + \
	props->player.pos.relative.x;
	props->player.pos.exact.y = props->player.pos.chunk.y + \
	props->player.pos.relative.y;
}

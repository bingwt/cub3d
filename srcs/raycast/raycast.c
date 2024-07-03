/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:08:12 by btan              #+#    #+#             */
/*   Updated: 2024/07/03 14:39:26 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	collision(t_vec2 pos, t_props *props)
{
	int	x;
	int	y;

	x = pos.x;
	y = pos.y;
	if (x < 0 || x >= props->map.width || y < 0 || y >= props->map.height)
		return (1);
	if (props->map.matrix[y][x] == 1)
		return (1);
	return (0);
}

int dda_line(t_vec2 start, t_vec2 end, t_props *props)
{
	t_vec2	delta;
	t_vec2	step;
	float	steps;
	int		i;

	delta.x = end.x - start.x;
    delta.y = end.y - start.y;
    steps = fmaxf(fabsf(delta.x), fabsf(delta.y));    
    step.x = delta.x / steps;
    step.y = delta.y / steps;
	i = 0;
    while (i < steps)
	{
		start.x += step.x;
		start.y += step.y;
		if (collision(start, props))
			return (1);
		i++;
	}
	return (0);
}

t_vec2	cast_ray(t_vec2 pos, t_vec2 dir, t_props *props)
{
	t_vec2	end;

	end = pos;
	vec2_add(&end, &dir);
	if (dda_line(pos, end, props))
		return (pos);
	return (cast_ray(end, dir, props));
}

void	cast_rays(t_props *props)
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	end;

	pos = props->player.pos.exact;
	dir.x = 0;
	dir.y = -1;
	
	end = cast_ray(pos, dir, props);
	printf("end: %f, %f\n", end.x, end.y);
}
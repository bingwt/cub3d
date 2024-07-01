/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:08:12 by btan              #+#    #+#             */
/*   Updated: 2024/07/01 15:23:28 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(t_vec2 a, t_vec2 b)
{
	t_vec2	delta;
	float	steps;
	t_vec2	step;
	int		i;

	delta.x = b.x - a.x;
	delta.y = b.y - a.y;
    steps = fmaxf(fabsf(delta.x), fabsf(delta.y));
	step.x = delta.x / steps;
	step.y = delta.y / steps;
	i = 0;
	while (i <= steps)
	{
		printf("Pixel: (%d, %d)\n", (int) a.x, (int) a.y);
        a.x += step.x;
        a.y += step.y;
		i++;

	}
}
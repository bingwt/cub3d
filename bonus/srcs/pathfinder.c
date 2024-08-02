/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:48:33 by btan              #+#    #+#             */
/*   Updated: 2024/08/02 17:56:22 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bot_start_pos(t_props *props)
{
	int	x;
	int	y;

	y = 0;
	while (y < props->map.height)
	{
		x = 0;
		while (x < props->map.width)
		{
			if (props->map.matrix[y][x] > 3)
			{
				props->bot.pos.exact.x = x;
				props->bot.pos.exact.y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

float	calc_dist(t_vec2 start, t_vec2 end)
{
	float	dist;

	dist = sqrt(pow(end.x - start.x, 2)) + sqrt(pow(end.y - start.y, 2));
	return (dist);
}

void	update_bot_pos(t_props *props)
{
	t_vec2	pos;

	pos.x = props->bot.pos.exact.x;
	pos.y = props->bot.pos.exact.y;
	printf("time: %ld\n", time_ms(props->bot_time));
	if (time_ms(props->bot_time) > 1000)
	{
		props->bot.pos.exact.x++;
		props->bot_time = time_ms(0);
		props->bot.pos.exact.x++;
		printf("bot: (x: %f,  y: %f)\n", props->bot.pos.exact.x, props->bot.pos.exact.y);
	}
}

void    test_pathfinder(t_props *props)
{
    bot_start_pos(props);
	update_bot_pos(props);
	props->bot.goal = calc_dist(props->player.pos.exact, props->bot.pos.exact);
	printf("goal: %f\n", props->bot.goal);
}
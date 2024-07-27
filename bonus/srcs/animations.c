/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:23:30 by btan              #+#    #+#             */
/*   Updated: 2024/07/28 02:43:01 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	time_ms(long start)
{
	struct timeval	s_time;
	time_t			timestamp;

	gettimeofday(&s_time, NULL);
	timestamp = ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000)) - start;
	return (timestamp);
}

void	update_frame(t_props *props)
{
	if (time_ms(props->current_time) > 100)
	{
		props->current_time = time_ms(0);
		props->player.status_frame++;
		if (props->player.status_frame > 10)
			props->player.status_frame = 5;
	}
}
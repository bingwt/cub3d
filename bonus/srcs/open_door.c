/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 05:37:57 by btan              #+#    #+#             */
/*   Updated: 2024/07/28 23:44:06 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_open_door(t_props *props)
{
	props->open[0].img = load_img("./assets/frames/open/1.xpm", 0, props);
	props->open[1].img = load_img("./assets/frames/open/2.xpm", 1, props);
	props->open[2].img = load_img("./assets/frames/open/3.xpm", 2, props);
	props->open[3].img = load_img("./assets/frames/open/4.xpm", 3, props);
	props->open[4].img = load_img("./assets/frames/open/5.xpm", 4, props);
	props->open[5].img = load_img("./assets/frames/open/6.xpm", 5, props);
}

void	update_door(t_props *props)
{
	if (time_ms(props->door_time) > 50)
	{
		props->door_time = time_ms(0);
		if (props->door_frame == 5)
			return ;
		props->door_frame++;
	}
}

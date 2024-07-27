/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_animation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 05:37:57 by btan              #+#    #+#             */
/*   Updated: 2024/07/28 06:20:18 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_block(t_props *props)
{
	props->blocks[0].img = load_img("./assets/frames/block/1.xpm", 0, props);
	props->blocks[1].img = load_img("./assets/frames/block/2.xpm", 1, props);
	props->blocks[2].img = load_img("./assets/frames/block/3.xpm", 2, props);
	props->blocks[3].img = load_img("./assets/frames/block/4.xpm", 3, props);
	props->blocks[4].img = load_img("./assets/frames/block/5.xpm", 4, props);
	props->blocks[5].img = load_img("./assets/frames/block/6.xpm", 5, props);
	props->blocks[6].img = load_img("./assets/frames/block/7.xpm", 6, props);
	props->blocks[7].img = load_img("./assets/frames/block/8.xpm", 7, props);
	props->blocks[8].img = load_img("./assets/frames/block/9.xpm", 8, props);
	props->blocks[9].img = load_img("./assets/frames/block/10.xpm", 9, props);
	props->blocks[10].img = load_img("./assets/frames/block/11.xpm", 10, props);
	props->blocks[11].img = load_img("./assets/frames/block/12.xpm", 11, props);
	props->blocks[12].img = load_img("./assets/frames/block/13.xpm", 12, props);
	props->blocks[13].img = load_img("./assets/frames/block/14.xpm", 13, props);
	props->blocks[14].img = load_img("./assets/frames/block/15.xpm", 14, props);
	props->blocks[15].img = load_img("./assets/frames/block/16.xpm", 15, props);
}

void	load_door(t_props *props)
{
	props->blocks[16].img = load_img("./assets/frames/door/1.xpm", 0, props);
	props->blocks[17].img = load_img("./assets/frames/door/2.xpm", 1, props);
	props->blocks[18].img = load_img("./assets/frames/door/3.xpm", 2, props);
	props->blocks[19].img = load_img("./assets/frames/door/4.xpm", 3, props);
	props->blocks[20].img = load_img("./assets/frames/door/5.xpm", 4, props);
	props->blocks[21].img = load_img("./assets/frames/door/6.xpm", 5, props);
	props->blocks[22].img = load_img("./assets/frames/door/7.xpm", 6, props);
	props->blocks[23].img = load_img("./assets/frames/door/8.xpm", 7, props);
	props->blocks[24].img = load_img("./assets/frames/door/9.xpm", 8, props);
	props->blocks[25].img = load_img("./assets/frames/door/10.xpm", 9, props);
	props->blocks[26].img = load_img("./assets/frames/door/11.xpm", 10, props);
	props->blocks[27].img = load_img("./assets/frames/door/12.xpm", 11, props);
	props->blocks[28].img = load_img("./assets/frames/door/13.xpm", 12, props);
	props->blocks[29].img = load_img("./assets/frames/door/14.xpm", 13, props);
	props->blocks[30].img = load_img("./assets/frames/door/15.xpm", 14, props);
	props->blocks[31].img = load_img("./assets/frames/door/16.xpm", 15, props);
}

void	update_frames(t_props *props)
{
	if (time_ms(props->frame_time) > 5)
	{
		props->frame_time = time_ms(0);
		if (props->player.place_frame == 23)
			return ;
		props->player.place_frame++;
	}
}

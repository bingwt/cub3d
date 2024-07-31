/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 03:01:08 by btan              #+#    #+#             */
/*   Updated: 2024/08/01 03:18:34 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	collect(t_props *props)
{
	t_vec2	pos;
	int		**map;

	pos = props->player.pos.exact;
	map = props->map.matrix;
	if (((int) pos.x - 1 < 0 || (int) pos.x + 1 > props->map.width) || \
			((int) pos.y - 1 < 0 || (int) pos.y + 1 > props->map.height))
		return ;
	if (map[(int) pos.y][(int) pos.x] == 3)
	{
		props->player.coins++;
		map[(int) pos.y][(int) pos.x] = 0;
	}
}

void	draw_coins(t_props *props)
{
	t_vec2	start;
	t_vec2	scale;
	t_img	*sprite;

	sprite = &props->coin[props->coin_frame].img;
	start.x = (WIDTH / 8) * 7;
	start.y = (HEIGHT / 8) * 6;
	scale.x = sprite->width * 0.25;
	scale.y = sprite->height * 0.25;
	if (props->player.coins > 0)
		draw_tex(start, scale, sprite, props);
	if (props->player.coins > 1)
	{
		start.x = (HEIGHT / 8) * 6.5;
		draw_tex(start, scale, sprite, props);
	}
	if (props->player.coins > 2)
	{
		start.x = (HEIGHT / 8) * 6;
		draw_tex(start, scale, sprite, props);
	}
}
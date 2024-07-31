/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:27:25 by btan              #+#    #+#             */
/*   Updated: 2024/08/01 03:05:16 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_hotbar(t_props *props)
{
	t_vec2	start;
	t_vec2	scale;
	int		hand;
	t_img	*hotbar;

	hand = props->player.hand - 1;
	hotbar = &props->hud[hand].img;
	start.x = WIDTH / 2 - hotbar->width / 4;
	start.y = (HEIGHT / 4) * 3;
	scale.x = WIDTH / 4;
	scale.y = HEIGHT / 4;
	draw_tex(start, scale, hotbar, props);
}

t_img	*equip_hand(int hand, t_props *props)
{
	t_img	*sprite;

	if (hand == 1)
	{
		if (props->player.place_frame <= 8)
			sprite = &props->blocks[props->player.place_frame].img;
		else
			sprite = &props->blocks[props->player.place_frame - 8].img;
	}
	if (hand == 2)
	{
		if (props->player.place_frame <= 8)
			sprite = &props->blocks[props->player.place_frame + 16].img;
		else
			sprite = &props->blocks[props->player.place_frame + 16 - 8].img;
	}
	return (sprite);
}

void	draw_hand(t_props *props)
{
	t_vec2	start;
	t_vec2	scale;
	int		hand;
	t_img	*sprite;

	start.x = HEIGHT / 2;
	start.y = HEIGHT / 2;
	scale.x = WIDTH / 2;
	scale.y = HEIGHT / 2;
	hand = props->player.hand - 1;
	sprite = &props->hud[hand + 2].img;
	if ((props->player.place_frame > 8 && \
	props->player.place_frame < 16))
		return ;
	sprite = equip_hand(hand, props);
	if (hand != 0)
		draw_tex(start, scale, sprite, props);
}

void	draw_status(t_props *props)
{
	t_vec2	start;
	t_vec2	scale;
	t_img	*sprite;

	sprite = &props->hud[props->player.status_frame].img;
	start.x = -(WIDTH / 8);
	start.y = (HEIGHT / 8) * 5;
	scale.x = sprite->width;
	scale.y = sprite->height;
	if (props->player.no_clip == 1)
		draw_tex(start, scale, sprite, props);
}

void	draw_hud(t_props *props)
{
	t_vec2	point;

	draw_hand(props);
	draw_hotbar(props);
	draw_status(props);
	draw_coins(props);
	point.x = 502;
	point.y = 512;
	while (point.x < 522)
	{
		fill_point(point, 3, 0x808080, props);
		point.x += 1;
	}
	point.x = 512;
	point.y = 502;
	while (point.y < 522)
	{
		fill_point(point, 3, 0x808080, props);
		point.y += 1;
	}
}

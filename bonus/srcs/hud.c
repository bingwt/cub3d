/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:27:25 by btan              #+#    #+#             */
/*   Updated: 2024/07/28 02:43:38 by btan             ###   ########.fr       */
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
	draw_texture(start, scale, hotbar, props);
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
	if (hand != 0)
		draw_texture(start, scale, sprite, props);
}

void	draw_crosshair(t_props *props)
{
	t_vec2	point;

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

void	draw_status(t_props *props)
{
	t_vec2	start;
	t_vec2	res;
	t_img	*sprite;

	sprite = &props->hud[props->player.status_frame].img;
	start.x = 0;
	start.y = (HEIGHT / 4) * 3;
	res.x = sprite->width / 4;
	res.y = sprite->height;
	if (props->player.no_clip == 1)
		texture_alt(start, res, sprite, props);
}

void	draw_hud(t_props *props)
{
	draw_hand(props);
	draw_hotbar(props);
	draw_status(props);
	draw_crosshair(props);
}

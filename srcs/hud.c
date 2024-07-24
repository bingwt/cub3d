/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:27:25 by btan              #+#    #+#             */
/*   Updated: 2024/07/24 16:53:13 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_hotbar(t_props *props)
{
	t_vec2	start;
	int		hand;
	t_img	*hotbar;

	start.x = 0;
	start.y = (HEIGHT / 4) * 3;
	hand = props->player.hand - 1;
	hotbar = &props->hud[hand].img;
	draw_texture(start, WIDTH / 4, hotbar, props);
}

void	draw_hand(t_props *props)
{
	t_vec2	start;
	int		hand;
	t_img	*sprite;

	start.x = HEIGHT / 2;
	start.y = HEIGHT / 2;
	hand = props->player.hand - 1;
	sprite = &props->hud[hand + 2].img;
	draw_texture(start, WIDTH / 2, sprite, props);
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

void	draw_hud(t_props *props)
{
	draw_hand(props);
	draw_hotbar(props);
	draw_crosshair(props);
}

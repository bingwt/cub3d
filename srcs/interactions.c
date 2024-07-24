/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:24:53 by btan              #+#    #+#             */
/*   Updated: 2024/07/24 13:39:21 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_interact_pos(t_vec2 *dir, t_props *props)
{
	dir->x = (int) props->player.pos.exact.x;
	dir->y = (int) props->player.pos.exact.y;
	if (props->player.angle >= 315 || props->player.angle < 45)
		dir->y = (int) props->player.pos.exact.y - 1;
	else if (props->player.angle >= 45 && props->player.angle < 135)
		dir->x = (int) props->player.pos.exact.x + 1;
	else if (props->player.angle >= 135 && props->player.angle < 225)
		dir->y = (int) props->player.pos.exact.y + 1;
	else
		dir->x = props->player.pos.exact.x - 1;
}

void	interact(t_action action, t_props *props)
{
	t_vec2	dir;

	set_interact_pos(&dir, props);
	if (((int) dir.x - 1 < 0 || (int) dir.x + 1 > props->map.width) || \
			((int) dir.y - 1 < 0 || (int) dir.y + 1 > props->map.height))
		return ;
	if (action == PLACE)
	{
		if (props->player.hand == 2 && !props->map.has_door)
			return ;
		if (props->map.matrix[(int) dir.y][(int) dir.x] != props->player.hand)
			props->map.matrix[(int) dir.y][(int) dir.x] = props->player.hand;
	}
	else if (action == INTERACT)
	{
		if (abs(props->map.matrix[(int) dir.y][(int) dir.x]) == 2)
			props->map.matrix[(int) dir.y][(int) dir.x] = \
			-props->map.matrix[(int) dir.y][(int) dir.x];
	}
	else if (action == CLEAR)
		props->map.matrix[(int) dir.y][(int) dir.x] = 0;
}

void	hotbar_select(int key, t_props *props)
{
	if (key == 49)
		props->player.hand = 1;
	else if (key == 50)
		props->player.hand = 2;
}

void	interact_key(int key, t_props *props)
{
	if (key == 99)
		interact(CLEAR, props);
	else if (key == 101)
		interact(INTERACT, props);
	else if (key == 102)
		interact(PLACE, props);
}

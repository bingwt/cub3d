/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 05:24:53 by btan              #+#    #+#             */
/*   Updated: 2024/07/24 05:27:19 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

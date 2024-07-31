/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 03:01:08 by btan              #+#    #+#             */
/*   Updated: 2024/08/01 03:01:19 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	collect(t_props *props)
{
	t_vec2	pos;
	int		**map;

	pos = props->player.pos.exact;
	map = props->map.matrix;
	if (map[(int) pos.y][(int) pos.x] == 3)
	{
		props->player.coins++;
		map[(int) pos.y][(int) pos.x] = 0;
	}
	printf("coins: %d\n", props->player.coins);
}
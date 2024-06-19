/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 11:53:19 by btan              #+#    #+#             */
/*   Updated: 2024/06/03 14:46:30 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_cell(t_props *props)
{
	t_color	color;
	int		*bounds;
	int		x;
	int		y;

	color.red = 0;
	color.green = 0;
	color.blue = 128;
	props->pixel.color = rgb_to_dec(&color);
	bounds = props->map.bounds;
	y = bounds[props->mouse.cell[0]];
	if (check_cell(props->mouse.cell[0], props->mouse.cell[1], props))
	{
		while (y++ < bounds[props->mouse.cell[0] + 1])
		{
			x = bounds[props->mouse.cell[1]];
			while (x < bounds[props->mouse.cell[1] + 1])
				draw_pixel(x++, y, props);
		}
	}
}

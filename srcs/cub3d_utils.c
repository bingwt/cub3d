/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:40:47 by btan              #+#    #+#             */
/*   Updated: 2024/06/01 22:29:18 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi_base(const char *str, const char *base)
{
	int	i;
	int	value;
	int	neg;
	int	base_len;

	i = 0;
	value = 0;
	neg = 1;
	base_len = ft_strlen(base);
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] != '\0')
	{
		if (ft_strchr(base, str[i]) == NULL)
			return (value * neg);
		value = value * base_len + ft_strchr(base, str[i]) - base;
		i++;
	}
	return (value * neg);
}

void	draw_background(t_props *props)
{
	int	x;
	int	y;

	y = 0;
	printf("%d\n", props->pixel.color);
	while (y++ < props->height)
	{
		x = 0;
		while (x < props->width)
			draw_pixel(++x, y, props);
	}
}

void	draw_grid(t_props *props)
{
	t_color color;
	t_color grid;
	int	gap;
	int	x;
	int	y;

	grid.red = 128;
	grid.green = 128;
	grid.blue = 128;
	props->pixel.color = rgb_to_dec(&grid);
	gap = WIDTH / TILE_SIZE;
	y = 0;
	while (y++ < props->height)
	{
		x = 0;
		if (!(x % gap) || !(y % gap))
		{
			props->pixel.color = rgb_to_dec(&grid);
		}
		while (x < props->width)
		{
			if (!(x % gap) || !(y % gap))
				draw_pixel(x, y, props);
			x++;
		}
	}
}

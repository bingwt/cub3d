/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:40:47 by btan              #+#    #+#             */
/*   Updated: 2024/07/24 02:07:23 by btan             ###   ########.fr       */
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

void	ft_swap(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	handle_toggles(int key, t_props *props)
{
	if (key == 108)
		props->player.mouse_movement = -props->player.mouse_movement;
	else if (key == 109)
		props->player.minimap = -props->player.minimap;
	else if (key == 110)
		props->player.no_clip = -props->player.no_clip;
}

void	clear_display(t_props *props)
{
	int	x;
	int	y;

	props->pixel.color = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			draw_pixel(x++, y, props);
		y++;
	}
}

void	loop(t_props *props)
{
	clear_display(props);
	draw_ceiling_floor(props);
	cast_rays(props);
	if (props->player.minimap == 1)
		draw_minimap(props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

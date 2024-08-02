/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:40:47 by btan              #+#    #+#             */
/*   Updated: 2024/08/02 15:56:01 by btan             ###   ########.fr       */
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
	if (!BONUS)
		return ;
	if (key == 103)
	{
		if (props->animated > 0)
			props->animated = 0;
		else
			props->animated = 1;
	}
	else if (key == 104)
		props->player.hotbar = -props->player.hotbar;
	else if (key == 108)
		props->player.mouse_movement = -props->player.mouse_movement;
	else if (key == 109)
		props->player.minimap = -props->player.minimap;
	else if (key == 110)
		props->player.no_clip = -props->player.no_clip;
	else if (key == 112)
		props->pause = -props->pause;
}

void	draw_pause(t_props *props)
{
	t_vec2	start;
	t_vec2	scale;
	t_img	*sprite;

	sprite = &props->paused.img;
	start.x = WIDTH / 4;
	start.y = HEIGHT / 4;
	scale.x = sprite->width;
	scale.y = sprite->height;
	draw_tex(start, scale, sprite, props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

void	loop(t_props *props)
{
	if (props->pause == 1)
	{
		draw_pause(props);
		return ;
	}
	update_status(props);
	draw_ceiling_floor(props);
	if (props->middle_dist > 0 && props->middle_dist < 230)
		draw_enemy(props);
	// enemy_cast(props);
	cast_rays(props);
	layer2_cast(props);
	if (props->middle_dist > 0 && props->middle_dist > 230)
		draw_enemy(props);
	if (props->player.minimap == 1)
		draw_minimap(props);
	if (props->animated)
		update_animated(props);
	update_frames(props);
	update_coin(props);
	if (props->player.hotbar == 1)
		draw_hud(props);
	mlx_mouse_get_pos(props->mlx, props->window, \
	&props->mouse.x, &props->mouse.y);
	if (!props->mouse.l_btn)
		mlx_mouse_move(props->mlx, props->window, WIDTH / 2, HEIGHT / 2);
	if (props->player.pos.exact.x)
		collect(props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

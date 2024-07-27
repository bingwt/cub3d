/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:04:00 by btan              #+#    #+#             */
/*   Updated: 2024/07/28 01:00:43 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_close(t_props *props)
{
	int	i;

	i = 0;
	free(props->title);
	while (i < 4)
		mlx_destroy_image(props->mlx, props->textures[i++].img.ptr);
	if (props->map.has_door)
		mlx_destroy_image(props->mlx, props->door_tex.img.ptr);
	i = 0;
	while (i < 5)
		mlx_destroy_image(props->mlx, props->hud[i++].img.ptr);
	free(props->map.no);
	free(props->map.ea);
	free(props->map.so);
	free(props->map.we);
	mlx_destroy_image(props->mlx, props->image);
	mlx_destroy_window(props->mlx, props->window);
	mlx_destroy_display(props->mlx);
	free(props->mlx);
	i = 0;
	while (i < props->map.height)
		free(props->map.matrix[i++]);
	free(props->map.matrix);
	free(props);
	exit(0);
}

int	handle_coords(int x, int y, t_props *props)
{
	(void) x;
	(void) y;
	if (props->player.mouse_movement == -1)
		return (1);
	if (props->mouse.x == WIDTH / 2)
		return (1);
	if (props->mouse.x < WIDTH / 2)
	{
		props->player.angle = props->player.angle - 1;
		if (props->player.angle < 0)
			props->player.angle = props->player.angle + 360;
	}
	else if (props->mouse.x > WIDTH / 2)
	{
		props->player.angle = props->player.angle + 1;
		if (props->player.angle > 360)
			props->player.angle = props->player.angle - 360;
	}
	return (0);
}

int	handle_keydown(int key, t_props *props)
{
	if (key == 97 || key == 100 || key == 115 || key == 119 || \
		key == 65505 || key == 65507)
		handle_movement(key, props);
	else if (key >= '0' && key <= '9')
		props->player.hand = key - '0';
	else if (key == 99 || key == 101 || key == 102)
		interact_key(key, props);
	else if (key == 104 || key == 108 || key == 109 || key == 110)
		handle_toggles(key, props);
	else if (key == 65307)
		handle_close(props);
	else if (key == 65361)
	{
		props->player.angle = props->player.angle - 10;
		if (props->player.angle < 0)
			props->player.angle = props->player.angle + 360;
	}
	else if (key == 65363)
	{
		props->player.angle = props->player.angle + 10;
		if (props->player.angle > 360)
			props->player.angle = props->player.angle - 360;
	}
	return (0);
}

int	handle_button(int btn, int x, int y, t_props *props)
{
	(void) y;
	if (btn == 1 && !props->mouse.l_btn)
	{
		interact_btn(btn, props);
		props->mouse.l_btn = 1;
		props->mouse.hold = x;
	}
	else if (btn == 1 && props->mouse.l_btn)
		props->mouse.l_btn = 0;
	if (btn == 3 && !props->mouse.r_btn)
	{
		interact_btn(btn, props);
		props->mouse.r_btn = 1;
	}
	else if (btn == 3 && props->mouse.r_btn)
		props->mouse.r_btn = 0;
	return (0);
}

void	handle_events(t_props *props)
{
	mlx_hook(props->window, 2, 1L << 0, handle_keydown, props);
	mlx_hook(props->window, 4, 1L << 2, handle_button, props);
	mlx_hook(props->window, 5, 1L << 3, handle_button, props);
	mlx_hook(props->window, 6, 1L << 6, handle_coords, props);
	mlx_hook(props->window, 17, 0L, handle_close, props);
}

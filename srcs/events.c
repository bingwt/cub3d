/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:04:00 by btan              #+#    #+#             */
/*   Updated: 2024/07/16 14:42:10 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_close(t_props *props)
{
	int	i;

	i = 0;
	while (i < 4)
		mlx_destroy_image(props->mlx, props->textures[i++].img.ptr);
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
	{
		free(props->map.matrix[i]);
		i++;
	}
	free(props->map.matrix);
	free(props);
	exit(0);
}

int	handle_coords(int x, int y, t_props *props)
{
	props->mouse.x = x;
	props->mouse.y = y;
	if (props->player.mouse_movement == -1)
		return (1);
	if (props->mouse.l_btn)
	{
		if (props->mouse.hold - x > 0)
			props->player.angle = props->player.angle - 1;
		else
			props->player.angle = props->player.angle + 1;
		if (props->player.angle < 0)
			props->player.angle = props->player.angle + 360;
	}
	return (0);
}

int	handle_keydown(int key, t_props *props)
{
	printf("%d\n", key);
	if (key == 97 || key == 100 || key == 115 || key == 119 || \
		key == 65505 || key == 65507)
		handle_movement(key, props);
	else if (key == 102)
		cell_action(WALL, props);
	else if (key == 99)
		cell_action(CLEAR, props);
	else if (key == 108)
		props->player.mouse_movement = -props->player.mouse_movement;
	else if (key == 109)
		props->player.minimap = -props->player.minimap;
	else if (key == 110)
		props->player.no_clip = -props->player.no_clip;
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
		props->mouse.l_btn = 1;
		props->mouse.hold = x;
	}
	else if (btn == 1 && props->mouse.l_btn)
		props->mouse.l_btn = 0;
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

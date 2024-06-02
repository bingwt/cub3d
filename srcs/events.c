/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:04:00 by btan              #+#    #+#             */
/*   Updated: 2024/06/02 14:35:44 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_close(t_props *props)
{
	//int	i;

	mlx_destroy_image(props->mlx, props->image);
	mlx_destroy_window(props->mlx, props->window);
	mlx_destroy_display(props->mlx);
	free(props->mlx);
	//i = 0;
//	while (i < props->map.rows)
//	{
//		free(props->map.matrix[i]);
//		i++;
//	}
//	free(props->map.matrix);
	exit(0);
}

int	handle_mouse_coord(int x, int y, t_props *props)
{
//	printf("x: %d, y: %d\n", x, y);
	props->mouse.x = x;
	props->mouse.y = y;
	return (0);
}

int	handle_keydown(int key, t_props *props)

{
	printf("%d\n", key);
	if (key == 102)
		printf("Fill @ x: %d, y: %d\n", props->mouse.x, props->mouse.y);
	if (key == 65307)
		handle_close(props);
	return (0);
}

int	handle_button(int key, t_props *props)
{
	(void) props;
	printf("%d\n", key);
//	if (key == 1)
//		mlx_hook(props->window, 6, 1L << 6, handle_mouse_coord, props);
	return (0);
}

void	handle_events(t_props *props)
{
	mlx_hook(props->window, 2, 1L << 0, handle_keydown, props);
	//mlx_hook(props->window, 4, 1L << 2, handle_button, props);
	mlx_hook(props->window, 17, 0L, handle_close, props);
	mlx_mouse_hook(props->window, handle_button, props);
	mlx_hook(props->window, 6, 1L << 6, handle_mouse_coord, props);
}

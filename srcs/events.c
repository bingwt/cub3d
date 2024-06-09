/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:04:00 by btan              #+#    #+#             */
/*   Updated: 2024/06/09 17:16:22 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_close(t_props *props)
{
	int	i;

	mlx_destroy_image(props->mlx, props->image);
	mlx_destroy_window(props->mlx, props->window);
	mlx_destroy_display(props->mlx);
	free(props->player.pos);
	free(props->mlx);
	i = 0;
	while (i < props->map.rows)
	{
		free(props->map.matrix[i]);
		i++;
	}
	free(props->map.matrix);
	exit(0);
}

int	handle_coords(int x, int y, t_props *props)
{
//	printf("x: %d, y: %d\n", x, y);
	props->mouse.x = x;
	props->mouse.y = y;
	loop(props);
	return (0);
}

void	handle_movement(int key, t_props *props)
{
	t_vec2	*dir;

	dir = ft_calloc(1, sizeof(t_vec2));
	if (key == 119)
	{
		dir->x = 0;
		dir->y = -1;
	}
	else if (key == 115)
	{
		dir->x = 0;
		dir->y = 1;
	}
	else if (key == 97)
	{
		dir->x = -1;
		dir->y = 0;
	}
	else if (key == 100)
	{
		dir->x = 1;
		dir->y = 0;
	}
	else if (key == 65505)
	{
		props->player.speed += 1;
	}
	else if (key == 65507)
	{
		props->player.speed -= 1;
	}
	rotate(dir, props->player.angle);
	vec2_scale(dir, props->player.speed);
	vec2_add(props->player.pos, dir);
	free(dir);
	printf("x: %f, y: %f\n", props->player.pos->x, props->player.pos->y);
	loop(props);
}

int	handle_keydown(int key, t_props *props)

{
	printf("%d\n", key);
	if (key == 102)
	{
	//	printf("Fill @ (%d, %d)\n", props->mouse.x, props->mouse.y);
	//	printf("cell: %d\n", check_cell(props->mouse.x, props->mouse.y, props));
		if (!check_cell(props->mouse.x, props->mouse.y, props))
		{
			props->map.matrix[props->mouse.cell[0]][props->mouse.cell[1]] = 1;
			fill_cell(props);
		}
	}
	else if (key == 97  || key == 100 || key == 115 || key == 119 || key == 65505 || key == 65507)
		handle_movement(key, props);
	else if (key == 99)
	{
		if(check_cell(props->mouse.x, props->mouse.y, props))
			props->map.matrix[props->mouse.cell[0]][props->mouse.cell[1]] = 0;
	}
	else if (key == 112)
		printf("Player @ (%f, %f)\n", props->player.pos->x, props->player.pos->y);
	else if (key == 65307)
		handle_close(props);
	else if (key == 65361)
	{
		props->player.angle = props->player.angle - 10;
		if (props->player.angle < 0)
			props->player.angle = props->player.angle + 360;
		printf("angle: %f\n", props->player.angle);
	}
	else if (key == 65363)
	{
		props->player.angle = props->player.angle + 10;
		if (props->player.angle > 360)
			props->player.angle = props->player.angle - 360;
		printf("angle: %f\n", props->player.angle);
	}
	loop(props);
	return (0);
}

void	handle_events(t_props *props)
{
	mlx_hook(props->window, 2, 1L << 0, handle_keydown, props);
	//mlx_hook(props->window, 4, 1L << 2, handle_button, props);
	mlx_hook(props->window, 17, 0L, handle_close, props);
	mlx_hook(props->window, 6, 1L << 6, handle_coords, props);
}

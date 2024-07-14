/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:25:28 by xlow              #+#    #+#             */
/*   Updated: 2024/07/14 21:49:03 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_props *props)
{
	props->mlx = mlx_init();
	props->width = WIDTH;
	props->height = HEIGHT;
	props->mini_width = 256;
	props->mini_height = 256;
	props->tile_size = TILE_SIZE;
	props->window = mlx_new_window(props->mlx, props->width, \
	props->height, "cub3d");
	props->image = mlx_new_image(props->mlx, props->width, props->height);
}

void	init_player(t_props *props)
{
	props->player.size = 10;
	props->player.speed = 1;
	props->player.angle = 0;
	props->player.fov = 0;
	props->player.pos.relative.x = 0.5;
	props->player.pos.relative.y = 1;
	props->mouse.x = 64;
	props->mouse.y = 64;
	props->mouse.l_btn = 0;
}

void	player_start_pos(t_props *props)
{
	int	x;
	int	y;

	y = 0;
	while (y < props->map.height)
	{
		x = 0;
		while (x < props->map.width)
		{
			if (props->map.matrix[y][x] > 1)
			{
				props->player.pos.chunk.x = x;
				props->player.pos.chunk.y = y;
				props->player.pos.exact.x = x + props->player.pos.relative.x;
				props->player.pos.exact.y = y + props->player.pos.relative.y;
				props->player.pos.dir.x = 0;
				props->player.pos.dir.y = -1;
				return ;
			}
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_props	*props;

	if (argc != 2)
		return (error_msg(INVALID_ARGS, NULL));
	props = ft_calloc(1, sizeof(t_props));
	props->map = process_cub(argv[1], props);
	init_window(props);
	init_player(props);
	player_start_pos(props);
	load_textures(props);
	draw_ceiling_floor(props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
	handle_events(props);
	mlx_loop_hook(props->mlx, (void *) loop, props);
	mlx_loop(props->mlx);
	return (0);
}

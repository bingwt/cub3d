/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:25:28 by xlow              #+#    #+#             */
/*   Updated: 2024/07/28 23:38:08 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*init_title(char *file)
{
	char	**path;
	char	*title;

	path = ft_split(file, '/');
	title = ft_strjoin("cub3d - ", path[ft_squarelen(path) - 1]);
	ft_free_split(&path);
	return (title);
}

void	init_window(char *file, t_props *props)
{
	props->title = init_title(file);
	props->mlx = mlx_init();
	props->width = WIDTH;
	props->height = HEIGHT;
	props->mini_width = 256;
	props->mini_height = 256;
	props->tile_size = TILE_SIZE;
	props->window = mlx_new_window(props->mlx, props->width, \
	props->height, props->title);
	props->image = mlx_new_image(props->mlx, props->width, props->height);
	props->animated = 0;
	props->status_time = time_ms(0);
	props->animation_time = time_ms(0);
	props->frame_time = time_ms(0);
	props->door_frame = 0;
	props->door_time = time_ms(0);
	props->pause = -1;
}

void	init_player(t_props *props)
{
	props->player.hand = 1;
	props->player.speed = 1;
	props->player.angle = 0;
	props->player.mouse_movement = 1;
	props->player.hotbar = 1;
	props->player.minimap = -1;
	props->player.no_clip = -1;
	props->player.status_frame = 5;
	props->player.place_frame = 23;
	props->player.pos.relative.x = 0.5;
	props->player.pos.relative.y = 0.5;
	props->mouse.x = 64;
	props->mouse.y = 64;
	props->mouse.l_btn = 0;
	props->mouse.r_btn = 0;
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
			if (props->map.matrix[y][x] > 3)
			{
				props->player.angle = props->map.matrix[y][x];
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
	t_map	map;

	if (argc != 2)
		return (error_msg(INVALID_ARGS, NULL));
	map = process_cub(argv[1]);
	props = ft_calloc(1, sizeof(t_props));
	props->map = map;
	init_window(argv[1], props);
	init_player(props);
	player_start_pos(props);
	load_textures(props);
	load_animated(props);
	load_block(props);
	load_door(props);
	load_open_door(props);
	draw_ceiling_floor(props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
	handle_events(props);
	mlx_loop_hook(props->mlx, (void *) loop, props);
	mlx_loop(props->mlx);
	return (0);
}

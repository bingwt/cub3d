/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:25:28 by xlow              #+#    #+#             */
/*   Updated: 2024/07/01 15:31:58 by btan             ###   ########.fr       */
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
	props->player.speed = 5;
	props->player.angle = 0;
	props->player.fov = 0;
	props->player.pos.relative.x = 0.5;
	props->player.pos.relative.y = 1;
	props->mouse.x = 64;
	props->mouse.y = 64;
	props->mouse.l_btn = 0;
	// check_cell(props->player.pos->x, props->player.pos->y, props);
}

void	test_check_chunk(t_props *props)
{
	t_vec2	pos;
	int		width;
	int		height;

	width = props->map.width;
	height = props->map.height;
	pos.x = width / 2 + 0.5;
	pos.y = height / 2 + 0.5;
	printf("width: %d\n", width);
	printf("height: %d\n", height);
	printf("pos.x: %f\n", pos.x);
	printf("pos.y: %f\n", pos.y);
	printf("check_chunk: %d\n", check_chunk(pos, props));
}

//int	main(int argc, char **argv)
int	main(void)
{
	t_props	props;

	props.map = process_cub("./maps/squidward.cub");
	print_map(&props.map, &props);
	test_check_chunk(&props);
	init_window(&props);
	init_player(&props);
	draw_ceiling_floor(&props);
	mlx_put_image_to_window(props.mlx, props.window, props.image, 0, 0);
	handle_events(&props);
	mlx_loop(props.mlx);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:25:28 by xlow              #+#    #+#             */
/*   Updated: 2024/06/28 14:41:06 by btan             ###   ########.fr       */
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
	props->player.fov = 60;
	props->player.position.relative.x = 0.5;
	props->player.position.relative.y = 1;
	props->player.pos = ft_calloc(1, sizeof(t_vec2));
	props->player.pos->x = 128;
	props->player.pos->y = 192;
	props->player.los.x = 0;
	props->player.los.y = 0;
	props->mouse.x = 64;
	props->mouse.y = 64;
	props->mouse.l_btn = 0;
	// check_cell(props->player.pos->x, props->player.pos->y, props);
}

//int	main(int argc, char **argv)
int	main(void)
{
	t_props	props;

	props.map = process_cub("./maps/squidward.cub");
	init_window(&props);
	init_player(&props);
	// print_map(&props.map, &props);
	// props.pixel.color = rgb_to_dec(&color);
	// draw_background(&props);
	// draw_grid(&props);
	// player(&props);
	// loop(&props);
	draw_ceiling_floor(&props);
	mlx_put_image_to_window(props.mlx, props.window, props.image, 0, 0);
	handle_events(&props);
	mlx_loop(props.mlx);
	return (0);
}

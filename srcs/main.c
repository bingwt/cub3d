/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:25:28 by xlow              #+#    #+#             */
/*   Updated: 2024/06/02 18:46:01 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_props *props)
{
	props->mlx = mlx_init();
	props->width = WIDTH;
	props->height = HEIGHT;
	props->tile_size = TILE_SIZE;
	props->window = mlx_new_window(props->mlx, props->width, \
	props->height, "cub3d");
	props->image = mlx_new_image(props->mlx, props->width, props->height);
}

void	init_player(t_props *props)
{
	props->player.size = 10;
	props->player.speed = 1;
	props->player.x = 64;
	props->player.y = 64;
	props->mouse.x = 64;
	props->mouse.y = 64;
}

//int	main(int argc, char **argv)
int	main(void)
{
	int		i;
	t_color color;
	t_props	props;

//	if (argc == 2)
//		read_map(argv[1]);
	props.map.rows = TILE;
	props.map.cols = TILE;
	props.map.matrix = ft_calloc(props.map.rows, sizeof(int *));
	i = 0;
	while (i < props.map.cols)
		props.map.matrix[i++] = ft_calloc(props.map.cols, sizeof(int));
	color.red = 255;
	color.green = 255;
	color.blue = 255;
	init_window(&props);
	init_player(&props);
	props.pixel.color = rgb_to_dec(&color);
	draw_background(&props);
	draw_grid(&props);
	player(&props);
	loop(&props);
	mlx_put_image_to_window(props.mlx, props.window, props.image, 0, 0);
	handle_events(&props);
	mlx_loop(props.mlx);
	return (0);
}

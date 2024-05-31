/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:25:28 by xlow              #+#    #+#             */
/*   Updated: 2024/05/31 18:19:26 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_props *props)
{
	props->mlx = mlx_init();
	props->width = WIDTH;
	props->height = HEIGHT;
	props->window = mlx_new_window(props->mlx, props->width, \
	props->height, "cub3d");
	props->image = mlx_new_image(props->mlx, props->width, props->height);
}

//int	main(int argc, char **argv)
int	main(void)
{
	t_color color;
	t_props	props;

//	if (argc == 2)
//		read_map(argv[1]);
	color.red = 255;
	color.green = 255;
	color.blue = 255;
	init_window(&props);
	props.pixel.color = rgb_to_dec(&color);
	draw_background(&props);
	mlx_put_image_to_window(props.mlx, props.window, props.image, 0, 0);
	handle_events(&props);
	mlx_loop(props.mlx);
	return (0);
}

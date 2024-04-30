/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:25:28 by xlow              #+#    #+#             */
/*   Updated: 2024/04/30 21:32:27 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.window_ptr = mlx_new_window(mlx.mlx_ptr, 1000, 1000, "cub3D");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, 1000, 1000);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}

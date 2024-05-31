/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:04:00 by btan              #+#    #+#             */
/*   Updated: 2024/05/31 16:10:49 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_close(t_mlx *mlx)
{
	int	i;

	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->window_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	i = 0;
//	while (i < mlx->map.rows)
//	{
//		free(mlx->map.matrix[i]);
//		i++;
//	}
//	free(mlx->map.matrix);
	exit(0);
}

static int	handle_keydown(int key, t_mlx *mlx)

{
	printf("%d\n", key);
	if (key == 65307)
		handle_close(mlx);
	return (0);
}

void	handle_events(t_mlx *mlx)
{
	mlx_hook(mlx->window_ptr, 2, 1L << 0, handle_keydown, mlx);
	mlx_hook(mlx->window_ptr, 17, 0L, handle_close, mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:25:28 by xlow              #+#    #+#             */
/*   Updated: 2024/06/25 16:57:42 by btan             ###   ########.fr       */
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
	props->player.position.relative.x = 0.5;
	props->player.position.relative.y = 0.5;
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

void	print_map(t_map *map, t_props *props)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->matrix[y][x] > 1)
			{
				props->player.position.cell.x = x;
				props->player.position.cell.y = y;
				printf(YELLOW "P" RESET);
			}
			else if (map->matrix[y][x])
				printf(CYAN "%d" RESET, map->matrix[y][x]);
			else
				printf(BLACK "%d" RESET, map->matrix[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
	printf("Player @ cell[x: %d][y: %d]\n", (int) props->player.position.cell.x, (int) props->player.position.cell.y);
	printf("Player @ rela[x: %f][y: %f]\n\n", props->player.position.relative.x, props->player.position.relative.y);
}

int	goto_cell(t_vec2 cell, t_props *props)
{
	int	x;
	int	y;

	x = props->player.position.cell.x;
	y = props->player.position.cell.y;
	if (!props->map.matrix[(int) cell.y][(int) cell.x])
	{
		props->map.matrix[(int) cell.y][(int) cell.x] = 270;
		props->map.matrix[y][x] = 0;
		return (0);
	}
	return (1);
}

//int	main(int argc, char **argv)
int	main(void)
{
	t_props	props;

	props.map = process_cub("./maps/squidward.cub");
	init_window(&props);
	init_player(&props);
	print_map(&props.map, &props);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:40:47 by btan              #+#    #+#             */
/*   Updated: 2024/06/27 19:05:47 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi_base(const char *str, const char *base)
{
	int	i;
	int	value;
	int	neg;
	int	base_len;

	i = 0;
	value = 0;
	neg = 1;
	base_len = ft_strlen(base);
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -neg;
		i++;
	}
	while (str[i] != '\0')
	{
		if (ft_strchr(base, str[i]) == NULL)
			return (value * neg);
		value = value * base_len + ft_strchr(base, str[i]) - base;
		i++;
	}
	return (value * neg);
}

void	ft_swap(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	check_cell(int x, int y, t_props *props)
{
	int	col;
	int	row;
	int	i;

	col = 0;
	row = 0;
	i = 0;
	while (col < x)
	{
		col = props->map.bounds[i];
		if (x > col)
			i++;
	}
	if (col > 0)
		col = i - 1;
	else
		col = i;
	i = 0;
	while (row < y)
	{
		row = props->map.bounds[i];
		if (y > row)
			i++;
	}
	if (row > 0)
		row = i - 1;
	else
		row = i;
//	printf("matrix[%d][%d]\n", row, col);
//	printf("cell: %d\n", props->map.matrix[row][col]);
	props->mouse.cell[0] = row;
	props->mouse.cell[1] = col;
	return (props->map.matrix[row][col]);
}

void	draw_background(t_props *props)
{
	int		x;
	int		y;

	y = 0;
	while (y++ < props->mini_height)
	{
		x = 0;
		while (x < props->mini_width)
		{
			// if (check_cell(x, y, props))
			// 	props->pixel.color = rgb_to_dec(&cell);
			// else
				props->pixel.color = 16777215;
			draw_pixel(x++, y, props);
		}
	}
}

void	draw_grid(t_props *props)
{
	t_color grid;
	int	gap_x;
	int	gap_y;
	int	x;
	int	y;

	grid.red = 128;
	grid.green = 128;
	grid.blue = 128;
	props->pixel.color = rgb_to_dec(&grid);
	gap_x = props->mini_width / props->map.cols;
	gap_y = props->mini_height / props->map.rows;
	y = 0;
	while (y++ < props->mini_height)
	{
		x = 0;
		if (!(x % gap_x) || !(y % gap_y))
		{
			props->pixel.color = rgb_to_dec(&grid);
		}
		while (x < props->mini_width)
		{
			if (!(x % gap_x) || !(y % gap_y))
				draw_pixel(x, y, props);
			x++;
		}
	}
}

void	clear_display(t_props *props)
{
	int	x;
	int	y;

	props->pixel.color = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			draw_pixel(x++, y, props);
		y++;
	}
}

t_action	check_chunk(t_vec2 chunk, t_props *props)
{
	int			**map;
	t_action	type;

	map = props->map.matrix;
	type = (t_action) map[(int) chunk.y][(int) chunk.x];
	return (type);
}

int	cast_ray(t_vec2 point, t_props *props)
{
	int	**map;
	t_vec2	end;
	t_vec2	chunk;

	map = props->map.matrix;
	end.x = 0;
	end.y = -1;
	chunk = props->player.position.cell;
	vec2_add(&point, &end);
	while (check_chunk(chunk, props) != WALL)
	{
		vec2_add(&chunk, &end);
	}
	printf("end[%f][%f]\n", point.x, point.y);
	printf("chunk[%d][%d]-> %d\n\n", (int) chunk.x, (int) chunk.y, (int) check_chunk(chunk, props));
	return (1);
}
void	loop(t_props *props)
{
	// t_line	line;

	clear_display(props);
	// props->pixel.color = 16777215;
	// draw_background(props);
	// draw_grid(props);
	// player(props);
	// line.x0 = props->player.pos->x;
	// line.y0 = props->player.pos->y;
	// line.x1 = props->player.los.x;
	// line.y1 = props->player.los.y;
	// (void) line;
//	draw_bresenham(&line, props);
	// draw_dda(&line, props);
	// draw_rays(props->player.pos, props);
	draw_ceiling_floor(props);
	cast_ray(props->player.position.relative, props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

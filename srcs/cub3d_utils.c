/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:40:47 by btan              #+#    #+#             */
/*   Updated: 2024/06/04 23:30:36 by btan             ###   ########.fr       */
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
	t_color	cell;
	int		x;
	int		y;

	cell.red = 0;
	cell.green = 0;
	cell.blue = 128;
	y = 0;
	while (y++ < props->height)
	{
		x = 0;
		while (x < props->width)
		{
			if (check_cell(x, y, props))
				props->pixel.color = rgb_to_dec(&cell);
			else
				props->pixel.color = 16777215;
			draw_pixel(++x, y, props);
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
	gap_x = props->width / props->map.cols;
	gap_y = props->height / props->map.rows;
	y = 0;
	while (y++ < props->height)
	{
		x = 0;
		if (!(x % gap_x) || !(y % gap_y))
		{
			props->pixel.color = rgb_to_dec(&grid);
		}
		while (x < props->width)
		{
			if (!(x % gap_x) || !(y % gap_y))
				draw_pixel(x, y, props);
			x++;
		}
	}
}

void	loop(t_props *props)
{
	t_line	line;

	props->pixel.color = 16777215;
	draw_background(props);
	draw_grid(props);
	player(props);
	test_rotate(props);
	line.x0 = props->player.pos.x;
	line.y0 = props->player.pos.y;
	line.x1 = props->player.los.x;
	line.y1 = props->player.los.y;
//	draw_bresenham(&line, props);
	draw_dda(&line, props);
	mlx_put_image_to_window(props->mlx, props->window, props->image, 0, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:55:45 by btan              #+#    #+#             */
/*   Updated: 2024/07/12 19:20:29 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_pixel(int x, int y, t_props *props)
{
	char	*buffer;
	int		offset;
	int		pixel_bits;
	int		line_bytes;

	pixel_bits = props->img.pixel_bits;
	line_bytes = props->img.line_bytes;
	buffer = mlx_get_data_addr(props->image, &pixel_bits, \
	&line_bytes, &props->img.endian);
	offset = (line_bytes * y) + (x * (pixel_bits / 8));
	if ((props->pixel.color >> 24 & 0xFF) == 1)
		return ;
	if (x >= 0 && x < props->width && y >= 0 && y < props->height)
		*((unsigned int *)(offset + buffer)) = props->pixel.color;
}

void	color_pixel(int x, int y, int color, t_props *props)
{
	char	*buffer;
	int		offset;
	int		pixel_bits;
	int		line_bytes;

	pixel_bits = props->img.pixel_bits;
	line_bytes = props->img.line_bytes;
	buffer = mlx_get_data_addr(props->image, &pixel_bits, \
	&line_bytes, &props->img.endian);
	offset = (line_bytes * y) + (x * (pixel_bits / 8));
	if (x >= 0 && x < props->width && y >= 0 && y < props->height)
		*((unsigned int *)(offset + buffer)) = color;
}

int	rgb_to_dec(t_color *color)
{
	int	dec;

	if (!color)
		return (0);
	dec = 0;
	dec = dec + color->red * 256 * 256;
	dec = dec + color->green * 256;
	dec = dec + color->blue;
	return (dec);
}

int	hex_to_dec(char *hex)
{
	char	*base;

	base = "0123456789abcdef";
	return (ft_atoi_base(hex, base));
}

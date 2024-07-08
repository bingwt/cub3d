/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 21:14:26 by btan              #+#    #+#             */
/*   Updated: 2024/07/08 21:16:16 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	load_img(char *file, t_props *props)
{
	t_img	img;

	img.mlx = props->mlx;
	img.ptr = mlx_xpm_file_to_image(img.mlx, file, &img.width, &img.height);
	img.addr = mlx_get_data_addr(img.ptr, &img.pixel_bits, \
				&img.line_bytes, &img.endian);
	return (img);
}

void	load_textures(t_props *props)
{
	t_texture	*texture;

	texture = &props->textures[0];
	texture->img = load_img(props->map.no, props);
	texture->id = 'N';
	texture = &props->textures[1];
	texture->img = load_img(props->map.so, props);
	texture->id = 'S';
	texture = &props->textures[2];
	texture->img = load_img(props->map.we, props);
	texture->id = 'W';
	texture = &props->textures[3];
	texture->img = load_img(props->map.ea, props);
	texture->id = 'E';
}

int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;
	int		color;

	dst = img->addr + (y * img->line_bytes + x * (img->pixel_bits / 8));
	color = *((unsigned int *) dst);
	return (color);
}

int	shade_color(int color, float factor)
{
	t_color	*rgb;
	int		shade;

	rgb = dec_to_rgb(color);
	rgb->red = (unsigned char) (rgb->red * (1.0 - factor));
	rgb->green = (unsigned char) (rgb->green * (1.0 - factor));
	rgb->blue = (unsigned char) (rgb->blue * (1.0 - factor));
	shade = rgb_to_dec(rgb);
	free(rgb);
	return (shade);
}

int	color_wall(char wall_face, float distance_factor)
{
	t_color	color;

	color.red = (unsigned char) (0 * (1.0 - distance_factor));
	color.green = (unsigned char) (0 * (1.0 - distance_factor));
	color.blue = (unsigned char) (0 * (1.0 - distance_factor));
	if (wall_face == 'N')
		color.red = (unsigned char) (200 * (1.0 - distance_factor));
	else if (wall_face == 'E')
		color.green = (unsigned char) (200 * (1.0 - distance_factor));
	else if (wall_face == 'S')
		color.blue = (unsigned char) (200 * (1.0 - distance_factor));
	else if (wall_face == 'W')
	{
		color.red = (unsigned char) (200 * (1.0 - distance_factor));
		color.green = (unsigned char) (200 * (1.0 - distance_factor));
	}
	else
	{
		color.red = (unsigned char) (255 * (1.0 - distance_factor));
		color.green = (unsigned char) (255 * (1.0 - distance_factor));
		color.blue = (unsigned char) (255 * (1.0 - distance_factor));
	}
	return (rgb_to_dec(&color));
}
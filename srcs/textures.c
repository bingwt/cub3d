/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 21:14:26 by btan              #+#    #+#             */
/*   Updated: 2024/07/24 01:54:57 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_img_failed(t_props *props, int imgs)
{
	int	i;

	i = 0;
	free(props->title);
	while (i < imgs)
		mlx_destroy_image(props->mlx, props->textures[i++].img.ptr);
	free(props->map.no);
	free(props->map.ea);
	free(props->map.so);
	free(props->map.we);
	mlx_destroy_image(props->mlx, props->image);
	mlx_destroy_window(props->mlx, props->window);
	mlx_destroy_display(props->mlx);
	free(props->mlx);
	i = 0;
	while (i < props->map.height)
	{
		free(props->map.matrix[i]);
		i++;
	}
	free(props->map.matrix);
	free(props);
	error_msg(INVALID_XPM, NULL);
	exit(1);
}

t_img	load_img(char *file, int i, t_props *props)
{
	t_img	img;

	img.mlx = props->mlx;
	img.ptr = mlx_xpm_file_to_image(img.mlx, file, &img.width, &img.height);
	if (!img.ptr)
		load_img_failed(props, i);
	img.addr = mlx_get_data_addr(img.ptr, &img.pixel_bits, \
				&img.line_bytes, &img.endian);
	return (img);
}

void	load_textures(t_props *props)
{
	t_texture	*texture;

	texture = &props->textures[0];
	texture->img = load_img(props->map.no, 0, props);
	texture->id = 'N';
	texture = &props->textures[1];
	texture->img = load_img(props->map.so, 1, props);
	texture->id = 'S';
	texture = &props->textures[2];
	texture->img = load_img(props->map.we, 2, props);
	texture->id = 'W';
	texture = &props->textures[3];
	texture->img = load_img(props->map.ea, 3, props);
	texture->id = 'E';
	if (props->map.has_door)
	{
		texture = &props->door_tex;
		texture->img = load_img(props->map.dr, 4, props);
		texture->id = 'D';
	}
}

int	get_pixel_color(t_img *img, int x, int y)
{
	char	*dst;
	int		color;

	dst = img->addr + (y * img->line_bytes + x * (img->pixel_bits / 8));
	color = *((unsigned int *) dst);
	return (color);
}

void	texture_wall_slice(t_ray *ray, t_props *props, int x, t_img *texture)
{
	int		height;
	int		slice[2];
	float	step;
	float	tex_pos;

	height = (int)(props->height / ray->wall_dist);
	slice[0] = (-height / 2) + (props->height / 2);
	if (slice[0] < 0)
		slice[0] = 0;
	slice[1] = (height / 2) + (props->height / 2);
	if (slice[1] >= props->height)
		slice[1] = props->height - 1;
	step = 1.0 * texture->height / height;
	tex_pos = (slice[0] - props->height / 2 + height / 2) * step;
	while (slice[0] < slice[1])
	{
		props->pixel.color = get_pixel_color(texture, ray->texture_slice, \
		(int) tex_pos);
		if (props->pixel.color != 0)
			draw_pixel(x, slice[0], props);
		tex_pos += step;
		slice[0]++;
	}
}

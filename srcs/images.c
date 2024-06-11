/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:22:45 by btan              #+#    #+#             */
/*   Updated: 2024/06/11 16:33:59 by btan             ###   ########.fr       */
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

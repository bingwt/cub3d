/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:12:25 by xlow              #+#    #+#             */
/*   Updated: 2024/05/31 15:20:55 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"

typedef enum e_error
{
	FILE_NOT_FOUND,
	INVALID_EXT,
	INVALID_CHAR,
	UNCLOSED,
	MAP_NOT_LAST,
	WRONG_ORDER,
	INVALID_ID,
	INVALID_TEXTURE,
	INVALID_COLOR
}	t_error;

typedef	struct s_texture
{
	char	*id;
	char	*path;
}	t_texture;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_assets
{
	t_texture	*texture;
	t_color		floor;
	t_color		ceiling;
}	t_assets;

typedef struct s_map
{
	int			rows;
	int			cols;
	int			start;
	int			**matrix;
	t_assets	*assets;
}	t_map;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*window_ptr;
	void	*img_ptr;
	void	*img_addr;
}	t_mlx;

// ERRORS
int	error_msg(t_error error, char *arg);

// MAP
t_map	*read_map(char *file);

// PIXEL
void	draw_pixel(int x, int y, t_mlx *mlx);
t_color	*hex_to_rgb(char *hex);
t_color	*dec_to_rgb(int dec);
int		rgb_to_dec(t_color *color);

#endif

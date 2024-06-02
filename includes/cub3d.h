/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:12:25 by xlow              #+#    #+#             */
/*   Updated: 2024/06/02 15:05:03 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef WIDTH
#  define WIDTH 1024
# endif

# ifndef HEIGHT
#  define HEIGHT 1024
# endif

# ifndef TILE
#  define TILE 8
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 16
# endif

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

typedef struct s_pixel
{
	int		color;
	int		next_color;
	t_color	*step;
}	t_pixel;

typedef struct s_assets
{
	t_texture	*texture;
	t_color		floor;
	t_color		ceiling;
}	t_assets;

typedef struct s_image
{
	int	pixel_bits;
	int	line_bytes;
	int	endian;
}	t_img;

typedef struct s_map
{
	int			rows;
	int			cols;
	int			start;
	int			**matrix;
	t_assets	*assets;
}	t_map;

typedef struct s_mouse
{
	int	x;
	int	y;
}	t_mouse;

typedef struct s_player
{
	int	x;
	int	y;
}	t_player;

typedef struct s_prop
{
	void		*mlx;
	void		*window;
	void		*image;
	int			width;
	int			height;
	int			tile_size;
	t_pixel		pixel;
	t_img		img;
	t_map		map;
	t_mouse		mouse;
	t_player	player;
}	t_props;

// ERRORS
int	error_msg(t_error error, char *arg);

// UTILS
int	ft_atoi_base(const char *str, const char *base);
void	draw_background(t_props *props);
void	draw_grid(t_props *props);

// MAP
t_map	*read_map(char *file);

// EVENTS
void	handle_events(t_props *props);

// PIXEL
void	draw_pixel(int x, int y, t_props *props);
t_color	*hex_to_rgb(char *hex);
t_color	*dec_to_rgb(int dec);
int		rgb_to_dec(t_color *color);

// PLAYER
void	player(t_props *props);

#endif

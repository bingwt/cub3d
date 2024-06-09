/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:12:25 by xlow              #+#    #+#             */
/*   Updated: 2024/06/09 17:30:02 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef WIDTH
#  define WIDTH 256
# endif

# ifndef HEIGHT
#  define HEIGHT 256
# endif

# ifndef TILE
#  define TILE 16
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 16
# endif

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
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

typedef struct s_vec2
{
	float	x;
	float	y;
}	t_vec2;

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
	int			*bounds;
	int			**matrix;
	t_assets	*assets;
}	t_map;

typedef struct s_mouse
{
	int	x;
	int	y;
	int	cell[2];
}	t_mouse;

typedef struct s_player
{
	int		size;
	int		speed;
	float	angle;
	t_vec2	*pos;
	t_vec2	los;
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

typedef struct s_line
{
	float	x0;
	float	y0;
	float	x1;
	float	y1;
}	t_line;

// ERRORS
int	error_msg(t_error error, char *arg);

// UTILS
int		ft_atoi_base(const char *str, const char *base);
void	ft_swap(float *a, float *b);
int		check_cell(int x, int y, t_props *props);
void	draw_background(t_props *props);
void	draw_grid(t_props *props);
void	loop(t_props *props);

// MAP
t_map	*read_map(char *file);

// EVENTS
void	handle_events(t_props *props);

// PIXEL
void	draw_pixel(int x, int y, t_props *props);
t_color	*hex_to_rgb(char *hex);
t_color	*dec_to_rgb(int dec);
int		rgb_to_dec(t_color *color);

//VECTORS
void	vec2_add(t_vec2 *a, t_vec2 *b);
void	vec2_scale(t_vec2 *vec, float scale);

//MATRIX
// t_vec2	*matrix_to_vec2(float **matrix);
// float	**vec2_to_matrix(t_vec2 *vec);
// float	**matrix_mult(float **a, float **b);
// void	free_matrix(float **matrix);

//ROTATION
float	deg_to_rad(float deg);
void	rotate(t_vec2 *vec, float angle);

//RAYCAST
void	draw_bresenham(t_line *line, t_props *props);
void	draw_dda(t_line *line, t_props *props);
void	draw_ray(t_vec2 *player, t_props *props);

//WALL
void	fill_cell(t_props *props);

// PLAYER
void	fill_point(t_vec2, t_props *props);
void	player(t_props *props);

#endif

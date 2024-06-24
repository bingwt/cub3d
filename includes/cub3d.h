/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:12:25 by xlow              #+#    #+#             */
/*   Updated: 2024/06/24 16:34:15 by btan             ###   ########.fr       */
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
#  define TILE 16
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 16
# endif

# define NO_MASK 1
# define SO_MASK 2
# define EA_MASK 4
# define WE_MASK 8
# define F_MASK 16
# define C_MASK 32
# define ALL_MASK 63

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft.h"
# include <stdbool.h>

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
	int			width;
	int			height;
	int			*bounds;
	int			**matrix;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	t_color		floor;
	t_color		ceiling;
}	t_map;

typedef struct s_mouse
{
	int	x;
	int	y;
	int	cell[2];
	int	l_btn;
	int	hold;
}	t_mouse;

typedef struct s_player
{
	int		size;
	int		speed;
	float	angle;
	float	fov;
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
	int			mini_width;
	int			mini_height;
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

// UTILS
int		ft_atoi_base(const char *str, const char *base);
void	ft_swap(float *a, float *b);
int		check_cell(int x, int y, t_props *props);
void	draw_background(t_props *props);
void	draw_grid(t_props *props);
void	loop(t_props *props);

// EVENTS
void	handle_events(t_props *props);

// PIXEL
void	draw_pixel(int x, int y, t_props *props);
void	color_pixel(int x, int y, int color, t_props *props);
t_color	*hex_to_rgb(char *hex);
t_color	*dec_to_rgb(int dec);
int		rgb_to_dec(t_color *color);
int		hex_to_dec(char *hex);

// PRIMITIVES
void 	fill_area(t_vec2 start, t_vec2 end, int color, t_props *props);
void    draw_ceiling_floor(char type, t_props *props);
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
void	draw_rays(t_vec2 *player, t_props *props);

//WALL
void	fill_cell(t_props *props);

// PLAYER
void	fill_point(t_vec2, t_props *props);
void	player(t_props *props);

// CHECK_FILE
bool	ends_with_xpm(char *file);
bool	ends_with_cub(char *file);
bool	check_perms(char *file);

// CUB
t_map	process_cub(char *file);

// SCENE
t_map	set_scene(int fd);

// ASSIGN_SCENE
void	assign_textures(t_map *map, char ***lines);
void	assign_rgbs(t_map *map, char ***lines);

// RGB
bool	valid_rgbs(char ***lines);

// GNL_SKIP_NL
char	*gnl_skip_nl(int fd);

// FREE_MAP
void	free_texture_paths(t_map map);
void	free_map(t_map map);

// MAP
t_map	set_map(t_map map, int fd);

// VALIDATE_MAP
bool	valid_map(char **content);

// NORMALISE_MAP
int		longest_width(char **content);
char	**normalise_map(char **content);

// CONVERT_MAP
int	**convert_map(char **content);

#endif

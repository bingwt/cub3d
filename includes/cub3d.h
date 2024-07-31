/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:12:25 by xlow              #+#    #+#             */
/*   Updated: 2024/07/31 22:45:20 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"
# define BLACK "\x1b[30m"
# define RESET "\x1B[0m"

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

# ifndef BONUS
#  define BONUS 0
# endif

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include "libft.h"
# include <stdbool.h>
# include <sys/time.h>

typedef enum e_mask
{
	NO_MASK = 1,
	SO_MASK = 2,
	EA_MASK = 4,
	WE_MASK = 8,
	F_MASK = 16,
	C_MASK = 32,
	ALL_MASK = 63
}	t_mask;

typedef enum e_error
{
	INVALID_ARGS,
	FILE_NOT_FOUND,
	INVALID_EXT,
	INVALID_CHAR,
	UNCLOSED,
	MAP_NOT_LAST,
	WRONG_ORDER,
	INVALID_ID,
	INVALID_TEXTURE,
	INVALID_COLOR,
	INVALID_XPM
}	t_error;

typedef enum e_action
{
	CLEAR,
	PLACE,
	INTERACT
}	t_action;

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
	void	*mlx;
	void	*ptr;
	char	*addr;
	int		width;
	int		height;
	int		pixel_bits;
	int		line_bytes;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_texture
{
	char	id;
	t_img	img;
}	t_texture;

typedef struct s_map
{
	int			rows;
	int			cols;
	int			width;
	int			height;
	int			has_door;
	int			*bounds;
	int			**matrix;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	char		*dr;
	t_color		floor;
	t_color		ceiling;
}	t_map;

typedef struct s_mouse
{
	int	x;
	int	y;
	int	cell[2];
	int	l_btn;
	int	r_btn;
	int	hold;
}	t_mouse;

typedef struct s_pos
{
	t_vec2	chunk;
	t_vec2	relative;
	t_vec2	exact;
	t_vec2	dir;
}	t_pos;

typedef struct s_player
{
	int		hand;
	int		speed;
	int		angle;
	int		mouse_movement;
	int		hotbar;
	int		minimap;
	int		no_clip;
	int		status_frame;
	int		place_frame;
	t_pos	pos;
}	t_player;

typedef struct s_ray
{
	t_vec2	map;
	t_vec2	delta;
	t_vec2	step;
	t_vec2	grid;
	int		hit;
	char	grid_side;
	char	wall_face;
	float	wall_dist;
	float	hit_pos;
	int		texture_slice;
}	t_ray;

typedef struct s_prop
{
	char		*title;
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
	t_texture	textures[4];
	t_texture	door_tex;
	t_texture	hotbar[2];
	t_texture	sprite[5];
	t_texture	hud[10];
	t_texture	cat[17];
	t_texture	blocks[32];
	int			animated;
	long		status_time;
	int			texture_frame;
	long		animation_time;
	long		frame_time;
	int			pause;
	t_texture	paused;
}	t_props;

// UTILS
int		ft_atoi_base(const char *str, const char *base);
void	ft_swap(float *a, float *b);
void	handle_toggles(int key, t_props *props);
void	loop(t_props *props);

// ERRORS
int		error_msg(t_error error, char *arg);

// WORLD
void	print_map(t_map *map, t_props *props);
int		goto_cell(t_vec2 cell, t_props *props);
int		fill_front(t_props *props);

// TEXTURES
t_img	load_img(char *file, int i, t_props *props);
void	load_textures(t_props *props);
int		get_pixel_color(t_img *img, int x, int y);
void	texture_wall_slice(t_ray *ray, t_props *props, int x, t_img *texture);

// MOVEMENT
void	handle_movement(int key, t_props *props);

// EVENTS
void	handle_events(t_props *props);

// PIXEL
void	draw_pixel(int x, int y, t_props *props);
void	color_pixel(int x, int y, int color, t_props *props);
int		rgb_to_dec(t_color *color);
int		hex_to_dec(char *hex);

// PRIMITIVES
void	fill_area(t_vec2 start, t_vec2 end, int color, t_props *props);
void	draw_ceiling_floor(t_props *props);
void	fill_point(t_vec2 point, int size, int color, t_props *props);
void	draw_tex(t_vec2 start, t_vec2 scale, t_img *texture, t_props *props);

//VECTORS
void	vec2_add(t_vec2 *a, t_vec2 *b);
void	vec2_scale(t_vec2 *vec, float scale);
void	vec2_sub(t_vec2 *a, t_vec2 *b);

// ROTATION
float	deg_to_rad(float deg);
void	rotate(t_vec2 *vec, float angle);

// DDA
void	init_dda(t_ray *ray, t_props *props);
void	dda(t_ray *ray, t_props *props);

// RAYCAST
void	cast_rays(t_props *props);

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
bool	valid_map(t_map *map, char **content);

// NORMALISE_MAP
int		longest_width(char **content);
char	**normalise_map(char **content);

// CONVERT_MAP
int		**convert_map(char **content);

// MINIMAP
void	draw_minimap(t_props *props);

// INTERACTIONS
void	interact(t_action action, t_props *props);
void	interact_key(int key, t_props *props);
void	interact_btn(int btn, t_props *props);

// HUD
void	draw_hud(t_props *props);

// ANIMATION
long	time_ms(long start);
void	update_status(t_props *props);
void	load_animated(t_props *props);
void	update_animated(t_props *props);
void	load_block(t_props *props);
void	load_door(t_props *props);
void	update_frames(t_props *props);
void	free_textures(t_props *props);

#endif

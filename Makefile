# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:19:43 by btan              #+#    #+#              #
#    Updated: 2024/07/28 05:44:44 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

BONUS_NAME = cub3D_bonus

INCLUDES = includes

CC = cc

CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES)

LIBS = -lXext -lX11 -lm

SRCS = srcs/cub3d_errors.c \
	   srcs/cub3d_utils.c \
	   srcs/world.c \
	   srcs/map/assign_scene.c \
	   srcs/map/check_file.c \
	   srcs/map/convert_map.c \
	   srcs/map/cub.c \
	   srcs/map/free_map.c \
	   srcs/map/gnl_skip_nl.c \
	   srcs/map/map.c \
	   srcs/map/normalise_map.c \
	   srcs/map/rgb.c \
	   srcs/map/scene.c \
	   srcs/map/validate_map.c \
	   srcs/textures.c \
	   srcs/movement.c \
	   srcs/events.c \
	   srcs/vectors.c \
	   srcs/rotation.c \
	   srcs/raycast/pixel.c \
	   srcs/raycast/primitives.c \
	   srcs/raycast/dda.c \
	   srcs/raycast/raycast.c \
	   srcs/raycast/minimap.c \
	   srcs/interactions.c \
	   srcs/hud.c \
	   srcs/main.c

BONUS_SRCS = bonus/srcs/cub3d_errors.c \
	   bonus/srcs/cub3d_utils.c \
	   bonus/srcs/world.c \
	   bonus/srcs/map/assign_scene.c \
	   bonus/srcs/map/check_file.c \
	   bonus/srcs/map/convert_map.c \
	   bonus/srcs/map/cub.c \
	   bonus/srcs/map/free_map.c \
	   bonus/srcs/map/gnl_skip_nl.c \
	   bonus/srcs/map/map.c \
	   bonus/srcs/map/normalise_map.c \
	   bonus/srcs/map/rgb.c \
	   bonus/srcs/map/scene.c \
	   bonus/srcs/map/validate_map.c \
	   bonus/srcs/textures.c \
	   bonus/srcs/movement.c \
	   bonus/srcs/events.c \
	   bonus/srcs/vectors.c \
	   bonus/srcs/rotation.c \
	   bonus/srcs/raycast/pixel.c \
	   bonus/srcs/raycast/primitives.c \
	   bonus/srcs/raycast/dda.c \
	   bonus/srcs/raycast/raycast.c \
	   bonus/srcs/raycast/minimap.c \
	   bonus/srcs/interactions.c \
	   bonus/srcs/hud.c \
	   bonus/srcs/animations.c \
	   bonus/srcs/place_animation.c \
	   bonus/srcs/main.c

OBJECTS = $(SRCS:.c=.o)

BONUS_OBJECTS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) libft/libft.a mlx/libmlx_Linux.a
	$(CC) $(CFLAGS) $^ -o $@ -Llibft -Lmlx -lft -lmlx $(LIBS)

$(BONUS_NAME): $(BONUS_OBJECTS) libft/libft.a mlx/libmlx_Linux.a
	$(CC) $(CFLAGS) $^ -o $@ -Llibft -Lmlx -lft -lmlx $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft/libft.a:
	make -C libft

mlx/libmlx_Linux.a:
	make -C mlx

clean:
	make clean -C libft
	rm -rf $(OBJECTS)
	rm -rf $(BONUS_OBJECTS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf $(BONUS_NAME)

bonus: CFLAGS += -g -D BONUS=1
bonus: $(BONUS_NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re bonus debug

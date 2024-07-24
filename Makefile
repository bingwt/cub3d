# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:19:43 by btan              #+#    #+#              #
#    Updated: 2024/07/24 13:28:53 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

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

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) libft/libft.a mlx/libmlx_Linux.a
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

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug

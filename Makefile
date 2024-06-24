# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:19:43 by btan              #+#    #+#              #
#    Updated: 2024/06/24 16:35:51 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

INCLUDES = includes

CC = cc

CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES)

LIBS = -lXext -lX11 -lm

SRCS = srcs/cub3d_errors.c \
	   srcs/cub3d_utils.c \
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
	   srcs/events.c \
	   srcs/vectors.c \
	   srcs/rotation.c \
	   srcs/raycast/pixel.c \
	   srcs/raycast/primitives.c \
	   srcs/raycast/wall.c \
	   srcs/raycast/raycast_utils.c \
	   srcs/raycast/dda.c \
	   srcs/player.c \
	   srcs/main.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(SRCS) $(OBJECTS) libft/libft.a mlx/libmlx_Linux.a $(INCLUDES)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) libft/libft.a mlx/libmlx_Linux.a $(LIBS)

libft/libft.a:
	make -C libft

mlx/libmlx_Linux.a:
	make -C mlx

clean:
	make clean -C libft
	rm -rf $(OBJECTS) $(NAME)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

map:
	cc map_checker.c map_utils.c cub3d_errors.c libft/libft.a -g -o validator

debug: CFLAGS += -g
debug: re

debug-noflag: CFLAGS = -I$(INCLUDES) -g
debug-noflag: re

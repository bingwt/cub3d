# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/03 14:19:43 by btan              #+#    #+#              #
#    Updated: 2024/05/31 15:22:10 by btan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

INCLUDES = includes

CC = cc

CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES)

LIBS = -lXext -lX11

SRCS = srcs/handle_errors/cub3d_errors.c \
	   srcs/main.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) libft/libft.a mlx/libmlx_Linux.a $(INCLUDES)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:41:11 by btan              #+#    #+#             */
/*   Updated: 2024/07/14 21:39:48 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_msg(t_error error, char *arg)
{
	printf("Error\n");
	if (error == INVALID_ARGS)
		printf("cub3D: invalid arguments\nUsage: ./cub3D <map.cub>\n");
	else if (error == FILE_NOT_FOUND)
		printf("cub3D: map path not found: %s\n", arg);
	else if (error == INVALID_EXT)
		printf("cub3D: invalid extension:'%s'\n", arg);
	else if (error == INVALID_CHAR)
		printf("cub3D: map can only contain, \e[1m0, 1, N, S, E, W\e[m.\n");
	else if (error == UNCLOSED)
		printf("cub3D: map is unclosed.\n");
	else if (error == MAP_NOT_LAST)
		printf("cub3D: invalid map order.\n");
	else if (error == WRONG_ORDER)
		printf("cub3D: invalid texture order.\n");
	else if (error == INVALID_ID)
		printf("cub3D: invalid identifier.\n");
	else if (error == INVALID_TEXTURE)
		printf("cub3D: invald texture path or texture path not found.\n");
	else if (error == INVALID_COLOR)
		printf("cub3D: invalid colors\n");
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:41:11 by btan              #+#    #+#             */
/*   Updated: 2024/05/03 17:05:52 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error_msg(t_error error, char *arg)
{
	printf("Error\n");
	if (error == FILE_NOT_FOUND)
		printf("Map: Map path not found.\n");
	else if (error == INVALID_EXT)
		printf("Map: '%s' is invalid: File must end with \".cub\".\n", arg);
	else if (error == INVALID_CHAR)
		printf("Map: Map must only contain, \e[1m0, 1, N, S, E, W\e[m.\n");
	else if (error == UNCLOSED)
		printf("Map: Provided map is unclosed.\n");
	else if (error == MAP_NOT_LAST)
		printf("Map: Invalid map order.\n");
	else if (error == WRONG_ORDER)
		printf("Map: Invalid Texture order.\n");
	else if (error == INVALID_ID)
		printf("Map: Invalid identifier.\n");
	else if (error == INVALID_TEXTURE)
		printf("Map: Invald texture path or texture path not found.\n");
	else if (error == INVALID_COLOR)
		printf("Map: Invalid colors, must be R,G,B colors in range [0 - 255]\n");
	return (1);
}

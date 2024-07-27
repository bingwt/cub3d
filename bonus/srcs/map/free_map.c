/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:45:12 by xlow              #+#    #+#             */
/*   Updated: 2024/07/17 19:45:13 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_texture_paths(t_map map)
{
	if (map.no)
		free(map.no);
	if (map.so)
		free(map.so);
	if (map.ea)
		free(map.ea);
	if (map.we)
		free(map.we);
}

static void	free_map_matrix(t_map map)
{
	int	i;

	i = 0;
	if (!map.matrix)
		return ;
	while (i < map.height)
	{
		free(map.matrix[i]);
		i++;
	}
	free(map.matrix);
}

void	free_map(t_map map)
{
	free_texture_paths(map);
	free_map_matrix(map);
}

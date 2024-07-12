/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:06:32 by xlow              #+#    #+#             */
/*   Updated: 2024/07/12 18:44:11 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	process_cub(char *file)
{
	int		fd;
	t_map	map;

	if (!ends_with_cub(file))
		exit(error_msg(INVALID_EXT, file));
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(".cub");
		exit(error_msg(FILE_NOT_FOUND, file));
	}
	map = set_scene(fd);
	if (!map.no)
	{
		close(fd);
		exit(1);
	}
	map = set_map(map, fd);
	return (map);
}

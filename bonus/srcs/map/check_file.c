/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:06:22 by xlow              #+#    #+#             */
/*   Updated: 2024/07/22 21:45:55 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ends_with_xpm(char *file)
{
	if (!ft_strrchr(file, '.') || ft_strcmp(ft_strrchr(file, '.'), ".xpm"))
		return (false);
	return (true);
}

bool	ends_with_cub(char *file)
{
	if (!ft_strrchr(file, '.') || ft_strcmp(ft_strrchr(file, '.'), ".cub"))
		return (false);
	return (true);
}

bool	check_perms(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1 || read(fd, 0, 0) < 0)
		return (false);
	close(fd);
	return (true);
}

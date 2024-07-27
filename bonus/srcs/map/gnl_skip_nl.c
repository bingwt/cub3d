/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_skip_nl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 19:44:24 by xlow              #+#    #+#             */
/*   Updated: 2024/07/17 19:44:26 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*gnl_skip_nl(int fd)
{
	char	*str;

	str = get_next_line(fd);
	while (str && !ft_strcmp(str, "\n"))
	{
		free(str);
		str = get_next_line(fd);
	}
	return (str);
}

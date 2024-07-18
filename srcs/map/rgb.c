/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:06:45 by xlow              #+#    #+#             */
/*   Updated: 2024/06/14 18:07:19 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_number(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isdigit(input[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

static bool	is_rgb_range(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_number(input[i]))
			return (false);
		if (ft_atoi(input[i]) > 255 || ft_atoi(input[i]) < 0)
			return (false);
		i++;
	}
	return (true);
}

bool	valid_rgbs(char ***lines)
{
	int		i;
	char	**c;
	char	**f;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(lines[i][0], "C") && ft_occ(lines[i][1], ',') == 3)
			c = ft_split(lines[i][1], ',');
		else if (!ft_strcmp(lines[i][0], "F") && ft_occ(lines[i][1], ',') == 3)
			f = ft_split(lines[i][1], ',');
		i++;
	}
	if (ft_squarelen(c) != 3 || ft_squarelen(f) != 3
		|| !is_rgb_range(c) || !is_rgb_range(f))
	{
		printf("Error\nInvalid floor or ceiling input\n");
		ft_free_split(&c);
		ft_free_split(&f);
		return (false);
	}
	ft_free_split(&c);
	ft_free_split(&f);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:38:55 by btan              #+#    #+#             */
/*   Updated: 2024/06/09 17:05:24 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	deg_to_rad(float deg)
{
	return (deg * (M_PI / 180));
}

void	rotate(t_vec2 *vec, float angle)
{
	t_vec2	*new_vec;

	new_vec = ft_calloc(1, sizeof(t_vec2));
	new_vec->x = vec->x * cos(deg_to_rad(angle)) - vec->y * sin(deg_to_rad(angle));
	new_vec->y = vec->x * sin(deg_to_rad(angle)) + vec->y * cos(deg_to_rad(angle));
	vec->x = new_vec->x;
	vec->y = new_vec->y;
	free(new_vec);
}
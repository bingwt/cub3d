/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:23:12 by btan              #+#    #+#             */
/*   Updated: 2024/07/14 20:56:24 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	vec2_add(t_vec2 *a, t_vec2 *b)
{
	a->x += b->x;
	a->y += b->y;
}

void	vec2_scale(t_vec2 *vec, float scale)
{
	vec->x *= scale;
	vec->y *= scale;
}

void	vec2_sub(t_vec2 *a, t_vec2 *b)
{
	a->x -= b->x;
	a->y -= b->y;
}
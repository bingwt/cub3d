/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:23:12 by btan              #+#    #+#             */
/*   Updated: 2024/06/09 16:32:07 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2	vec2_add(t_vec2 a, t_vec2 b)
{
	t_vec2	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	return (sum);
}

t_vec2	vec2_scale(t_vec2 vec, float scale)
{
	t_vec2	scaled;

	scaled.x = vec.x * scale;
	scaled.y = vec.y * scale;
	return (scaled);
}
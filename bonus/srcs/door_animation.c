/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:48:54 by btan              #+#    #+#             */
/*   Updated: 2024/08/01 22:58:19 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_re_doors(t_props *props)
{
	int		i;
	char	*n;
	char	*tmp;
	char	*path;

	i = 0;
	while (i < 28)
	{
		path = ft_strdup("./assets/frames/re_doors/");
		n = ft_itoa(i + 1);
		tmp = ft_strjoin(path, n);
		free(path);
		free(n);
		path = ft_strjoin(tmp, ".xpm");
		free(tmp);
		props->re_doors[i].img = load_img(path, i, props);
		free(path);
		i++;
	}
}

void	update_re_doors(int dir, t_props *props)
{
	if (time_ms(props->re_time) > 5)
	{
		props->re_time = time_ms(0);
		if (dir == -2 && props->re_frame < 27)
			props->re_frame++;
		else if (dir == 2 && props->re_frame > 0)
			props->re_frame--;
	}
}

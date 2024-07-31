/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 02:22:24 by btan              #+#    #+#             */
/*   Updated: 2024/08/01 03:22:06 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_coin(t_props *props)
{
	int		i;
	char	*n;
	char	*tmp;
	char	*path;

	i = 0;
	while (i < 30)
	{
		path = ft_strdup("./assets/frames/coin/");
		n = ft_itoa(i + 1);
		tmp = ft_strjoin(path, n);
		free(path);
		free(n);
		path = ft_strjoin(tmp, ".xpm");
		free(tmp);
		props->coin[i].img = load_img(path, i, props);
		free(path);
		i++;
	}
}

void	update_coin(t_props *props)
{
	if (time_ms(props->coin_time) > 50)
	{
		props->coin_time = time_ms(0);
		if (props->coin_frame == 29)
			props->coin_frame = 0 ;
		props->coin_frame++;
	}
}

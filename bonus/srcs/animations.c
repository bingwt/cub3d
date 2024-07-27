/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 01:23:30 by btan              #+#    #+#             */
/*   Updated: 2024/07/28 06:28:30 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	time_ms(long start)
{
	struct timeval	s_time;
	time_t			timestamp;

	gettimeofday(&s_time, NULL);
	timestamp = ((s_time.tv_sec * 1000) + (s_time.tv_usec / 1000)) - start;
	return (timestamp);
}

void	update_status(t_props *props)
{
	if (time_ms(props->status_time) > 100)
	{
		props->status_time = time_ms(0);
		props->player.status_frame++;
		if (props->player.status_frame > 10)
			props->player.status_frame = 5;
	}
}

void	load_animated(t_props *props)
{
	props->cat[0].img = load_img("./assets/frames/cat/1.xpm", 0, props);
	props->cat[1].img = load_img("./assets/frames/cat/2.xpm", 1, props);
	props->cat[2].img = load_img("./assets/frames/cat/3.xpm", 2, props);
	props->cat[3].img = load_img("./assets/frames/cat/4.xpm", 3, props);
	props->cat[4].img = load_img("./assets/frames/cat/5.xpm", 4, props);
	props->cat[5].img = load_img("./assets/frames/cat/6.xpm", 5, props);
	props->cat[6].img = load_img("./assets/frames/cat/7.xpm", 6, props);
	props->cat[7].img = load_img("./assets/frames/cat/8.xpm", 7, props);
	props->cat[8].img = load_img("./assets/frames/cat/9.xpm", 8, props);
	props->cat[9].img = load_img("./assets/frames/cat/10.xpm", 9, props);
	props->cat[10].img = load_img("./assets/frames/cat/11.xpm", 10, props);
	props->cat[11].img = load_img("./assets/frames/cat/12.xpm", 11, props);
	props->cat[12].img = load_img("./assets/frames/cat/13.xpm", 12, props);
	props->cat[13].img = load_img("./assets/frames/cat/14.xpm", 13, props);
	props->cat[14].img = load_img("./assets/frames/cat/15.xpm", 14, props);
	props->cat[15].img = load_img("./assets/frames/cat/16.xpm", 15, props);
	props->cat[16].img = load_img("./assets/frames/cat/17.xpm", 16, props);
}

void	update_animated(t_props *props)
{
	static int	dir;

	if (time_ms(props->animation_time) > 34)
	{
		props->animation_time = time_ms(0);
		if (props->animated == 1)
			dir = 1;
		if (props->animated == 17)
			dir = 0;
		if (dir)
			props->animated++;
		else
			props->animated--;
	}
}

void	free_textures(t_props *props)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (i < 4)
			mlx_destroy_image(props->mlx, props->textures[i].img.ptr);
		if (i < 11)
			mlx_destroy_image(props->mlx, props->hud[i].img.ptr);
		if (i < 17)
			mlx_destroy_image(props->mlx, props->cat[i].img.ptr);
		mlx_destroy_image(props->mlx, props->blocks[i++].img.ptr);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:12:25 by xlow              #+#    #+#             */
/*   Updated: 2024/05/02 23:51:30 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include "mlx.h"
# include "libft/libft.h"

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*window_ptr;
	void	*img_ptr;
	void	*img_addr;
}	t_mlx;

// MAP
void	read_map(char *file);

#endif

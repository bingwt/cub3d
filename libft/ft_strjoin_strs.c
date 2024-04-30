/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_strs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 20:22:17 by xlow              #+#    #+#             */
/*   Updated: 2024/04/07 20:22:18 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_strs(char **strs)
{
	int		i;
	char	*res;

	i = 0;
	if (!strs || ft_squarelen(strs) < 2)
		return (NULL);
	res = ft_strdup(strs[i]);
	i++;
	while (strs[i])
	{
		res = ft_strjoin_free(res, strs[i], res);
		i++;
	}
	return (res);
}

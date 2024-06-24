/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:47:26 by xlow              #+#    #+#             */
/*   Updated: 2024/06/24 20:49:32 by xlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_splitdup(char **content)
{
	int		i;
	char	**res;
	char	*lines;

	i = 0;
	if (!content)
		return (NULL);
	res = ft_calloc(sizeof(char *), ft_squarelen(content));
	while (content[i])
	{
		lines = ft_strdup(content[i]);
		res[i] = lines;
		i++;
	}
	return (res);
}

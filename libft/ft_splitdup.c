/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:47:26 by xlow              #+#    #+#             */
/*   Updated: 2024/06/24 21:04:41 by btan             ###   ########.fr       */
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
	res = ft_calloc(sizeof(char *), ft_squarelen(content) + 1);
	while (content[i])
	{
		lines = ft_strdup(content[i]);
		res[i] = lines;
		i++;
	}
	return (res);
}

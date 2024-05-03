/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:34:26 by btan              #+#    #+#             */
/*   Updated: 2024/05/02 23:49:31 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.c"

void	read_map(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		handle_error(file, "NO_FILE");
	if (!ft_strrchr(file, '.') || ft_strncmp(ft_strrchr(file, '.'), ".cub", 4))
		handle_error("map must end with '.cub'", "INVALID_INPUT");
	line = get_next_line(fd);
	printf("%s", line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		printf("%s", line);
	}
	close(fd);
}


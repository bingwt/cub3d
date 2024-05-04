/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:34:26 by btan              #+#    #+#             */
/*   Updated: 2024/05/05 00:24:11 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_iswhitespace(int c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}

void	read_texture(char *str)
{
	char	*ptr;
	char	**texture;
	char	*path;

	ptr = str;
	while (ft_iswhitespace(*ptr))
		ptr++;
	texture = ft_split(ptr, ' ');
	if (!texture)
		return ;
	if (texture[1])
	{
		path = ft_strdup(texture[1]);
		path[ft_strlen(path) - 1] = '\0';
		if (!ft_strcmp(texture[0], "NO"))
			printf("North path is: %s\n", path);
		else if (!ft_strcmp(texture[0], "SO"))
			printf("South path is: %s\n", path);
		else if (!ft_strcmp(texture[0], "WE"))
			printf("West path is: %s\n", path);
		else if (!ft_strcmp(texture[0], "EA"))
			printf("East path is %s\n", path);
		free(path);
	}
	ft_free_split(&texture);
}

void	read_map(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg(FILE_NOT_FOUND, NULL);
	if (!ft_strrchr(file, '.') || ft_strcmp(ft_strrchr(file, '.'), ".cub"))
		error_msg(INVALID_EXT, file);
	line = get_next_line(fd);
	read_texture(line);
	printf("%s", line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		read_texture(line);
		printf("%s", line);
	}
	close(fd);
}

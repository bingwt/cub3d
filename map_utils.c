/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:34:26 by btan              #+#    #+#             */
/*   Updated: 2024/05/05 14:27:23 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_iswhitespace(int c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (1);
	return (0);
}

void	read_texture(char *str, t_texture *texture)
{
	char		*ptr;
	char		**split;

	ptr = str;
	while (ft_iswhitespace(*ptr))
		ptr++;
	split = ft_split(ptr, ' ');
	if (!split)
		texture = NULL;
	texture->id = ft_strdup(split[0]);
	if (split[1])
	{
		texture->path = ft_strdup(split[1]);
		texture->path[ft_strlen(texture->path) - 1] = '\0';
		if (!ft_strcmp(texture->id, "NO"))
			printf("North path is: %s\n", texture->path);
		else if (!ft_strcmp(texture->id, "SO"))
			printf("South path is: %s\n", texture->path);
		else if (!ft_strcmp(texture->id, "WE"))
			printf("West path is: %s\n", texture->path);
		else if (!ft_strcmp(texture->id, "EA"))
			printf("East path is %s\n", texture->path);
	}
	ft_free_split(&split);
}

void	read_rgb(char *str)
{
	char	*ptr;
	char	**colors;
	char	*color;

	ptr = str;
	while (ft_iswhitespace(*ptr))
		ptr++;
	colors = ft_split(ptr, ' ');
	if (!colors)
		return ;
	if (colors[1])
	{
		color = ft_strdup(colors[1]);
		color[ft_strlen(color) - 1] = '\0';
		if (!ft_strcmp(colors[0], "F"))
			printf("Floor color is: %s\n", color);
		else if (!ft_strcmp(colors[0], "C"))
			printf("Ceiling color is: %s\n", color);
		free(color);
	}
	ft_free_split(&colors);
}

t_assets	*init_assets(int fd)
{
	t_assets	*assets;
	char		*line;
	int			i;

	assets = ft_calloc(1, sizeof(t_assets));
	assets->texture = ft_calloc(4, sizeof(t_texture));
	i = 0;
	while (i < 4)
	{
		line = get_next_line(fd);
		read_texture(line, &assets->texture[i++]);
		free(line);
	}
	return (assets);
}

t_map	*read_map(char *file)
{
	int			fd;
	t_map		*map;
	char		*line;

	fd = open(file, O_RDONLY);
	map = ft_calloc(1, sizeof(t_map));
	if (fd < 0)
		error_msg(FILE_NOT_FOUND, NULL);
	if (!ft_strrchr(file, '.') || ft_strcmp(ft_strrchr(file, '.'), ".cub"))
		error_msg(INVALID_EXT, file);
	map->assets = init_assets(fd);
	line = get_next_line(fd);
	printf("%s", line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		//read_texture(line);
		read_rgb(line);
		printf("%s", line);
	}
	close(fd);
	return (map);
}

//t_map	*read_map(char *file)
//{
//	int		i;
//	int		fd;
//	t_map	*map;
//	char	*line;
//	char	*ptr;
//
//	i = 0;
//	fd = open(file, O_RDONLY);
//	map = ft_calloc(1, sizeof(t_map));
//	if (fd < 0)
//		error_msg(FILE_NOT_FOUND, NULL);
//	if (!ft_strrchr(file, '.') || ft_strcmp(ft_strrchr(file, '.'), ".cub"))
//		error_msg(INVALID_EXT, file);
//	line = get_next_line(fd);
//	if (line)
//		i++;
//	read_texture(line);
//	printf("%s", line);
//	while (line)
//	{
//		free(line);
//		line = get_next_line(fd);
//		if (!line)
//			break ;
//		i++;
//		printf("line: %d: ", i); 
//		ptr = line;
//		read_texture(line);
//		read_rgb(line);
//		while (*ptr)
//		{
//			if (map->start)
//				break ;
//			if (!ft_iswhitespace(*ptr))
//			{
//				map->start = i;
//				break ;
//			}
//			ptr++;
//		}
//		printf("%s", line);
//	}
//	close(fd);
//	printf("start: %d\n", map->start);
//	return (map);
//}

//t_map	*init_map(char *file)
//{
//}

#include "cub3d.h"

t_map	process_cub(char *file)
{
	int		fd;
	t_map	map;

	if (!ends_with_cub(file))
		exit(1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(".cub");
		exit(1);
	}
	map = set_scene(fd);
	if (!map.no)
	{
		close(fd);
		exit(1);
	}
	return (map);
}

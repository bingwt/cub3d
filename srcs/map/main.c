#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map	map;

	map = process_cub(argv[1]);
	printf("%s\n%s\n%s\n%s\n", map.no, map.so, map.ea, map.we);
	printf("%d,%d,%d\n%d,%d,%d\n", map.ceiling.red, map.ceiling.green, map.ceiling.blue, map.floor.red, map.floor.green, map.floor.blue);
	free_map(map);
	return (0);
}

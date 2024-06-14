#include "cub3d.h"

void	free_map(t_map map)
{
	free(map.no);
	free(map.so);
	free(map.ea);
	free(map.we);
}
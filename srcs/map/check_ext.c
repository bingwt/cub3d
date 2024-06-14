#include "cub3d.h"

bool	ends_with_xpm(char *file)
{
	if (!ft_strrchr(file, '.') || ft_strcmp(ft_strrchr(file, '.'), ".xpm"))
		return (false);
	return (true);
}

bool	ends_with_cub(char *file)
{
	if (!ft_strrchr(file, '.') || ft_strcmp(ft_strrchr(file, '.'), ".cub"))
		return (false);
	return (true);
}

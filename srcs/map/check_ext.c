#include "cub3d.h"

bool	ends_with_xpm(char *file)
{
	if (!ft_strrchr(file, '.') || ft_strcmp(ft_strrchr(file, '.', ".xpm")))
	{
		printf("Error\nTexture file \"%s\" must end with \".xpm\"", file);
		return (false);
	}
	return (true);
}

bool	ends_with_cub(char *file)
{
	if (!ft_strrchr(file, '.') || ft_strcmp(ft_strrchr(file, '.', ".cub")))
	{
		printf("Error\nScene description file \"%s\" must end with \".cub\"", file);
		return (false);
	}
	return (true);
}

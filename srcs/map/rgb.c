#include "cub3d.h"

static bool	is_number(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isdigit(input[i]) == 0)
			return (false);
			i++;
	}
	return (true);
}

static bool is_rgb_range(char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_number(input[i]))
			return (false);
		if (ft_atoi(input[i]) > 255)
			return (false);
		i++;
	}
	return (true);
}

bool	valid_rgbs(char ***lines)
{
	int		i;
	char	**c;
	char	**f;

	i = 0;
	while (i < 6)
	{
		if (!ft_strcmp(lines[i][0], "C"))
			c = ft_split(lines[i][1], ',');
		else if (!ft_strcmp(lines[i][0], "F"))
			f = ft_split(lines[i][1], ',');
		i++;
	}
	if (ft_squarelen(c) != 3 || ft_squarelen(f) != 3
		|| !is_rgb_range(c) || !is_rgb_range(f))
	{
		printf("Error\nInvalid floor or ceiling input.");
		return (false);
	}
	ft_free_split(&c);
	ft_free_split(&f);
	return (true);
}
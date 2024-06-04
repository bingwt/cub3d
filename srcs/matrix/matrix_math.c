/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btan <btan@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:10:02 by btan              #+#    #+#             */
/*   Updated: 2024/06/04 23:34:45 by btan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec2	*matrix_to_vec2(float **matrix)
{
	t_vec2	*vec;

	vec = (t_vec2 *)malloc(sizeof(t_vec2));
	vec->x = matrix[0][0];
	vec->y = matrix[1][0];
	return (vec);
}

float	**vec2_to_matrix(t_vec2 *vec)
{
	float	**matrix;

	matrix = (float **)malloc(sizeof(float *) * 2);
	matrix[0] = (float *)malloc(sizeof(float) * 1);
	matrix[1] = (float *)malloc(sizeof(float) * 1);
	matrix[0][0] = vec->x;
	matrix[1][0] = vec->y;
	return (matrix);
}

float	**matrix_mult(float **a, float **b)
{
    float	**matrix;
    int		i;
    int		j;
    int		k;

    matrix = (float **)malloc(sizeof(float *) * 2);
    matrix[0] = (float *)malloc(sizeof(float) * 1);
    matrix[1] = (float *)malloc(sizeof(float) * 1);
    i = -1;
    while (++i < 2)
    {
        j = -1;
        while (++j < 1)
        {
            matrix[i][j] = 0;
            k = -1;
            while (++k < 2)
                matrix[i][j] += a[i][k] * b[k][j];
        }
    }
    return (matrix);
}

void	free_matrix(float **matrix)
{
    int	i;

    i = 0;
    while (i < 2)
        free(matrix[i++]);
    free(matrix);
}

void	rotate(float ***matrix, float degrees)
{
    double	angle;
    float	**rotation;
    float	**result;

    angle = degrees * (M_PI / 180);
    rotation = ft_calloc(2, sizeof(int *));
    rotation[0] = ft_calloc(2, sizeof(int));
    rotation[1] = ft_calloc(2, sizeof(int));
    rotation[0][0] = cos(angle);
    rotation[0][1] = -sin(angle);
    rotation[1][0] = sin(angle);
    rotation[1][1] = cos(angle);
    result = matrix_mult(rotation, *matrix);
    free_matrix(rotation);
    free_matrix(*matrix);
    *matrix = result;
}

void	test_rotate(t_props *props)
{
	float	**matrix_pos;
	float	**matrix_los;
	t_vec2	*temp;

	matrix_pos = vec2_to_matrix(&props->player.pos);
	matrix_los = vec2_to_matrix(&props->player.los);
	rotate(&matrix_pos, 0);
	rotate(&matrix_los, props->player.angle);
	temp = matrix_to_vec2(matrix_pos);
	props->player.pos.x = temp->x;
	props->player.pos.y = temp->y;
	free(temp);
	temp = matrix_to_vec2(matrix_los);
	props->player.los.x = temp->x;
	props->player.los.y = temp->y;
	free(temp);
	free_matrix(matrix_pos);
	free_matrix(matrix_los);
}

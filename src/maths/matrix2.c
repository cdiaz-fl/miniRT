/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:49:11 by cdiaz-fl          #+#    #+#             */
/*   Updated: 2022/04/26 09:24:06 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/matrix.h"
#include	<stdlib.h>

#include	<stdio.h> //quitar
t_mtx	mul_mtx(t_mtx *mtx1, t_mtx *mtx2)
{
	t_mtx	new;
	int		i;
	int		j;
	int		k;
	double	result;

	new = create_mtx(4);
	i = -1;
	while((unsigned int)++i < mtx1->size)
	{
		j = -1;
		while((unsigned int)++j < mtx1->size)
		{
			k = -1;
			result = 0.0f;
			while((unsigned int)++k < mtx1->size)
				result += mtx1->data[i][k] * mtx2->data[k][j];
			new.data[i][j] = result;
		}
	}
	return new;
}

double   *mul_mtx_tup(t_mtx *mtx, double *tup)
{
	double	*new;
	int		i;
	int		j;
	double	result;

	new = malloc(sizeof(double) * 4);
	if (!new)
	{
		perror("Error: ");
		//función de salida
	}
	i = -1;
	while((unsigned int)++i < mtx->size)
	{
		j = -1;
		result = 0.0f;
		while((unsigned int)++j < mtx->size)
			result += mtx->data[i][j] * tup[j];
		new[i] = result;
	}
	return new;
}

t_mtx	transpose_mtx(t_mtx *mtx)
{
	t_mtx	new;
	int		i;
	int		j;

	new = create_mtx(4);
	i = -1;
	while((unsigned int)++i < mtx->size)
	{
		j = -1;
		while((unsigned int)++j < mtx->size)
			new.data[j][i] = mtx->data[i][j];
	}
	return new;
}


t_mtx	sub_mtx(t_mtx *mtx, int x, int y)
{
	int						i;
	int						j;
	unsigned int	k;
	unsigned int	l;
	t_mtx					new;

	new = create_mtx(mtx->size - 1);
	i = -1;
	k = 0;
	l = 0;
	while((unsigned int)++i < mtx->size)
	{
		j = -1;
		while((unsigned int)++j < mtx->size)
		{
			if (i != x && j != y)
			{
				new.data[k][l] = mtx->data[i][j];
				l++;
				if ((unsigned int)l == new.size)
				{
					l = 0;
					k++;
				}
			}
		}
	}
	return new;
}

double	det_2d_mtx(t_mtx *mtx)
{
	double	det;

	det = (mtx->data[0][0] * mtx->data[1][1]);
	det -= (mtx->data[0][1] * mtx->data[1][0]);
	return det;
}

double	minor_3d_mtx(t_mtx *mtx, unsigned int x, unsigned int y)
{
	t_mtx		sub;
	double	result;

	sub = sub_mtx(mtx, x, y);
	result = det_2d_mtx(&sub);
	free_mtx(&sub);
	return result;
}

double	cofactor_3d_mtx(t_mtx *mtx, unsigned int x, unsigned int y)
{
	t_mtx		sub;
	double	result;

	//if (mtx->size >= 3)
	//{
		sub = sub_mtx(mtx, x, y);
		//result = cofactor_3d_mtx(&sub, x, y);
		result = det_2d_mtx(&sub);
		free_mtx(&sub);
	/*}
	else
	{
		result = det_2d_mtx(mtx);
		*/
		if ((x + y) % 2 != 0)
			result *= -1;
	//}
	return result;
}

double	cofactor_trash_mtx(t_mtx *mtx, unsigned int x, unsigned int y, unsigned int sum)
{
	t_mtx		sub;
	double	result;

		
	sub = sub_mtx(mtx, x, y);
	result = det_2d_mtx(&sub);
	free_mtx(&sub);
	if ((sum) % 2 != 0)
		result *= -1;
	return result;
}

double	det_mtx(t_mtx *mtx)
{
	double				det;
	unsigned int	i;
	t_mtx					sub;

	det = 0;
	i = 0;
	while (i < mtx->size)
	{
		if (mtx->size > 3)
		{
			sub = sub_mtx(mtx, 0, i);
			if (i % 2 != 0)
				det += (mtx->data[0][i] * det_mtx(&sub) * -1);
			else
				det += mtx->data[0][i] * det_mtx(&sub);
			free_mtx(&sub);
		}
		else
			det += mtx->data[0][i] * cofactor_3d_mtx(mtx, 0, i);
		i++;
	}
	return det;
}

t_mtx	create_cofactor_mtx(t_mtx *mtx)
{
	t_mtx	new;
	t_mtx	sub;
	int		x;
	int		y;

	new = create_mtx(mtx->size);
	x = -1;
	while ((unsigned int)++x < new.size)
	{
		y = -1;
		while ((unsigned int)++y < new.size)
		{
			sub = sub_mtx(mtx, x, y);
			new.data[x][y] = cofactor_trash_mtx(&sub, 0, 0, x + y) * sub.data[0][0];
			new.data[x][y] += cofactor_trash_mtx(&sub, 0, 1, x + y + 1) * sub.data[0][1]; 
			new.data[x][y] += cofactor_trash_mtx(&sub, 0, 2, x + y + 2) * sub.data[0][2];
			free_mtx(&sub);
		}
	}
	return new;
}

t_mtx	invert_mtx(t_mtx *mtx)
{
	t_mtx	new_original;
	t_mtx	new_trans;
	float	original_det;
	unsigned int	i;
	unsigned int	j;

	new_original = create_cofactor_mtx(mtx);
	original_det = det_mtx(mtx);
	new_trans = transpose_mtx(&new_original); 
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			new_trans.data[i][j] /= original_det;
			j++;
		}
		i++;
	}
	free_mtx(&new_original);
	return	new_trans;
}

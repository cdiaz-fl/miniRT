/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:49:11 by cdiaz-fl          #+#    #+#             */
/*   Updated: 2022/04/20 12:14:41 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include	"matrix.h"
#include	<stdio.h>
#include	<stdlib.h>

float		**create_mtx(void)
{
	float	**mtx;
	int		i;

	mtx = malloc((sizeof(float *) * 4));
	if (!mtx)
		return NULL;
	i = -1;
	while(++i < 4)
	{
			mtx[i] = malloc(sizeof(float) * 4);
			if (!mtx[i])
				return NULL;
	}
	return mtx;
}

float		**identity_mtx(unsigned int i)
{
	float	**mtx;
	int		j;

	mtx = malloc((sizeof(float *) * i));
	if (!mtx)
		return NULL;
	j = -1;
	while(++j < 4)
	{
			mtx[j] = calloc(sizeof(float) * i, 0);
			mtx[j][j] = 1;
			if (!mtx[j])
				return NULL;
	}
	return mtx;
}

void	print_mtx(float **mtx)
{
	int	i;
	int	j;

	i = -1;
	printf("---MATRIX----------\n");
	while(++i < 4)
	{
		j = -1;
		while(++j < 4)
			printf("[ %.2f ]  ", mtx[i][j]);
		printf("\n");
	}
}

void	init_mtx(float **mtx, float *array, unsigned int row)
{
	unsigned int i;

	i = 0;
	while (i < 4)
	{
		mtx[row][i] = array[i];
		i++;
	}
	return ;
}

void	free_mtx(float **mtx)
{
	int i;

	i = -1;
	while(++i < 4)
		free(mtx[i]);
	free(mtx);
}

float		**mul_mtx(float **mtx1, float **mtx2)
{
	float	**new;
	int		i;
	int		j;
	int		k;
	float	result;

	new = create_mtx();
	if (!new)
		return NULL;
	i = -1;
	while(++i < 4)
	{
		j = -1;
		while(++j < 4)
		{
			k = -1;
			result = 0.0f;
			while(++k < 4)
				result += mtx1[i][k] * mtx2[k][j];
			new[i][j] = result;
		}
	}
	return new;
}

float   *mul_mtx_tup(float **mtx, float *tup)
{
	float	*new;
	int		i;
	int		j;
	float	result;

	new = malloc(sizeof(float) * 4);
	if (!new)
		return NULL;
	i = -1;
	while(++i < 4)
	{
		j = -1;
		result = 0.0f;
		while(++j < 4)
			result += mtx[i][j] * tup[j];
		new[i] = result;
	}
	return new;
}


//Hay que borrar print tuple
void print_tuple(float *tpl)
{
	int i = -1;
	while (++i < 4)
		printf("[%d]%.2f ", i, tpl[i]);
	printf("\n");
}


int main()
{
	float	**mtx;
	float	array[4] = {1.0f, 0.0f, 2.0f, 3.0f};
	float	**mtx2;
	float	array2[4] = {5.0f, 4.0f, 2.0f, 2.0f};

	mtx = create_mtx();
	init_mtx(mtx, array, 0);
	init_mtx(mtx, array, 1);
	init_mtx(mtx, array, 2);
	init_mtx(mtx, array, 3);
	print_mtx(mtx);

	mtx2 = create_mtx();
	init_mtx(mtx2, array2, 0);
	init_mtx(mtx2, array2, 1);
	init_mtx(mtx2, array2, 2);
	init_mtx(mtx2, array2, 3);
	print_mtx(mtx2);

	float **mtx3;
	mtx3 = mul_mtx(mtx, mtx2);
	print_mtx(mtx3);


	float *tup;
	tup = mul_mtx_tup(mtx, array2);
	print_tuple(tup);

	float	**mtx4;
	mtx4 = identity_mtx(4);
	print_mtx(mtx4);

	free_mtx(mtx);
	free_mtx(mtx2);
	free_mtx(mtx3);
	free_mtx(mtx4);
	return 0;
}

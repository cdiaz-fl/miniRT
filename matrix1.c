/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:21:06 by cdiaz-fl          #+#    #+#             */
/*   Updated: 2022/04/25 09:14:46 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"matrix.h"
#include	<stdio.h>
#include	<stdlib.h>

t_mtx	create_mtx(unsigned int size)
{
	t_mtx		mtx;
	int			i;

	if (size < 2)
	{
		perror("Error: "); //este perror hay que quitar
		//función de salida
	}
	mtx.data = malloc(sizeof(double *) * size);
	if (!mtx.data)
	{
		perror("Error: ");
		//función de salida
	}
	i = -1;
	while((unsigned int)++i < size)
	{
			mtx.data[i] = malloc(sizeof(double) * size);
			if (!mtx.data[i]) //Falta liberar aquí cosas
			{
				perror("Error: ");
				//función de salida
			}
	}
	mtx.size = size;
	return mtx;
}


t_mtx	identity_mtx(unsigned int size)
{
	t_mtx	mtx;
	int		i;
	int		j;

	if (size < 2)
	{
		perror("Error: ");
		//función de salida
	}
	mtx = create_mtx(size);
	i = -1;
	while ((unsigned int)++i < size)
	{
		j = -1;
		while ((unsigned int)++j < size)
		{
			if (i == j)
				mtx.data[i][j] = 1.0;
			else
				mtx.data[i][j] = 0.0;
		}
	}
	return mtx;
}

void	print_mtx(t_mtx *mtx)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	printf("---MATRIX----------\n");
	while(i < mtx->size)
	{
		j = 0;
		while(j < mtx->size)
		{
			printf("[ %.5f ]  ", mtx->data[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	init_mtx(t_mtx *mtx, double *v, unsigned int row)
{
	unsigned int i;

	i = 0;
	while (i < mtx->size)
	{
		mtx->data[row][i] = v[i];
		i++;
	}
	return ;
}

void	free_mtx(t_mtx *mtx)
{
	unsigned int i;

	i = 0;
	while(i < mtx->size)
	{
		free(mtx->data[i]);
		i++;
	}
	free(mtx->data);
}

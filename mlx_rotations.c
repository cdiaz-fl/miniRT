/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_rotations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:35:59 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/20 13:48:57 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mtx_tranform.h"

double	**rotatation_x_mtx(double grade)
{
	double **mtx;

	mtx = identity_mtx; //Añadir la matriz identity
	if (!mtx)
		return (NULL);
	mtx[1][1] = cos((grade * M_PI) / 180);
	mtx[1][2] = sin((grade * M_PI) / 180) * (-1);
	mtx[2][1] = sin((grade * M_PI) / 180);
	mtx[2][2] = cos((grade * M_PI) / 180);
	return (mtx);
}

double	**rotatation_y_mtx(double grade)
{
	double **mtx;

	mtx = identity_mtx; //Añadir la matriz identity
	if (!mtx)
		return (NULL);
	mtx[0][0] = cos((grade * M_PI) / 180);
	mtx[0][2] = sin((grade * M_PI) / 180);
	mtx[2][0] = sin((grade * M_PI) / 180) * (-1);
	mtx[2][2] = cos((grade * M_PI) / 180);
	return (mtx);
}

double	**rotatation_z_mtx(double grade)
{
	double **mtx;

	mtx = identity_mtx; //Añadir la matriz identity
	if (!mtx)
		return (NULL);
	mtx[0][0] = cos((grade * M_PI) / 180);
	mtx[0][1] = sin((grade * M_PI) / 180) * (-1);
	mtx[1][0] = sin((grade * M_PI) / 180);
	mtx[1][1] = cos((grade * M_PI) / 180);
	return (mtx);
}

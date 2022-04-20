/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:17:44 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/20 12:13:04 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mtx_tranform.h"

float   **translation_mtx(float x, float y, float z)
{
	float **mtx;

	mtx = identity_mtx; //Añadir la matriz identity
	if (!mtx)
		return (NULL);
	mtx[0][4] = x;
	mtx[1][4] = y;
	mtx[2][4] = z;
	return (mtx);
}

float   **scaling_mtx(float x, float y, float z)
{
	float **mtx;

	mtx = identity_mtx; //Añadir la matriz identity
	if (!mtx)
		return (NULL);
	mtx[0][0] = x;
	mtx[1][1] = y;
	mtx[2][2] = z;
	return (mtx);
}

float   **shearing_mtx(float shear_arr[6])
{
	float **mtx;

	mtx = identity_mtx; //Añadir la matriz identity
	if (!mtx)
		return (NULL);
	mtx[0][1] = shear_arr[0];
	mtx[0][2] = shear_arr[1];
	mtx[1][0] = shear_arr[2];
	mtx[1][2] = shear_arr[3];
	mtx[2][0] = shear_arr[4];
	mtx[2][1] = shear_arr[4];
	return (mtx);
}

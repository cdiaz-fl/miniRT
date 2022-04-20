/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:09:48 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/20 13:51:14 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

double *scalar_mul_vec(double *tpl, double scalar)
{
	double *result;
	int i;

	result = (double *)malloc(sizeof(double) * 4);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < 3)
		result[i] = tpl[i] * scalar;
	result[3] = 1;
	return (result);
}

double *scalar_div_vec(double *tpl, double scalar)
{
	double *result;
	int i;

	result = (double *)malloc(sizeof(double) * 4);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < 3)
		result[i] = tpl[i] / scalar;
	result[3] = 1;
	return (result);
}

double dot_product_vec(double *tpl1, double *tpl2)
{
	double result;
	int i;
	
	result = 0;
	i = -1;
	while (++i < 3)
		result += tpl1[i] * tpl2[i];
	return (result);
}


double *cross_product_vec(double *a, double *b)
{
	double *result;
	int i;
	
	result = (double *)malloc(sizeof(double) * 4);
	if (!result)
		return (NULL);
	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = a[2] * b[0] - a[0] * b[2];
	result[2] = a[0] * b[1] - a[1] * b[0];
	result[3] = 1;
	return (result);
}


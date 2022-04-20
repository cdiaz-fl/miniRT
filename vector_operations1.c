/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:09:48 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/20 11:04:30 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float *scalar_mul_vec(float *tpl, float scalar)
{
	float *result;
	int i;

	result = (float *)malloc(sizeof(float) * 4);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < 3)
		result[i] = tpl[i] * scalar;
	result[3] = 1;
	return (result);
}

float *scalar_div_vec(float *tpl, float scalar)
{
	float *result;
	int i;

	result = (float *)malloc(sizeof(float) * 4);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < 3)
		result[i] = tpl[i] / scalar;
	result[3] = 1;
	return (result);
}

float dot_product_vec(float *tpl1, float *tpl2)
{
	float result;
	int i;
	
	result = 0;
	i = -1;
	while (++i < 3)
		result += tpl1[i] * tpl2[i];
	return (result);
}


float *cross_product_vec(float *a, float *b)
{
	float *result;
	int i;
	
	result = (float *)malloc(sizeof(float) * 4);
	if (!result)
		return (NULL);
	result[0] = a[1] * b[2] - a[2] * b[1];
	result[1] = a[2] * b[0] - a[0] * b[2];
	result[2] = a[0] * b[1] - a[1] * b[0];
	result[3] = 1;
	return (result);
}


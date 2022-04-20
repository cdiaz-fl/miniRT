/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:37:55 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/20 11:04:29 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "math.h"

float *neg_vec(float *tpl)
{
	float *result;
	int i;

	result = (float *)malloc(sizeof(float) * 4);
	i = -1;
	while (++i < 3)
		result[i] = tpl[i] * -1;
	result[3] = 1;
	return (result);
}

float magnitude_vec(float *tpl)
{
	int i;
	float result;

	i = -1;
	result = 0;
	while (++i < 3)
		result += tpl[i]  * tpl[i];
	return (sqrt(result));

}

float *normalization_vec(float *tpl, float magnitude)
{
	float *result;
	int i;

	result = (float *)malloc(sizeof(float) * 4);
	i = -1;
	while (++i < 3)
		result[i] = tpl[i] / magnitude;
	result[3] = 1;
	return (result);
}

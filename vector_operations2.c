/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:37:55 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/20 13:51:15 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "math.h"

double *neg_vec(double *tpl)
{
	double *result;
	int i;

	result = (double *)malloc(sizeof(double) * 4);
	i = -1;
	while (++i < 3)
		result[i] = tpl[i] * -1;
	result[3] = 1;
	return (result);
}

double magnitude_vec(double *tpl)
{
	int i;
	double result;

	i = -1;
	result = 0;
	while (++i < 3)
		result += tpl[i]  * tpl[i];
	return (sqrt(result));

}

double *normalization_vec(double *tpl, double magnitude)
{
	double *result;
	int i;

	result = (double *)malloc(sizeof(double) * 4);
	i = -1;
	while (++i < 3)
		result[i] = tpl[i] / magnitude;
	result[3] = 1;
	return (result);
}

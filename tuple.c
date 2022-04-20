/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:52:37 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/20 13:51:16 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

void print_tuple(double *tpl)
{
	int i = -1;
	while (++i < 4)
		printf("[%d]%.2f ", i, tpl[i]);
	printf("\n");
}

double *create_tuple(double x, double y, double z, double w)
{
	double *tuple;

	tuple = (double *)malloc(sizeof(double) * 4);
	if (!tuple)
		return (NULL);
	tuple[0] = x;
	tuple[1] = y;
	tuple[2] = z;
	tuple[3] = w;
	return (tuple);
}

double *add_tuple(double *tpl1, double* tpl2)
{
	double *add_tpl;
	int i;

	add_tpl = (double *)malloc(sizeof(double) * 4);
	if (!add_tpl)
		return (NULL);
	i = -1;
	while (++i < 4)
		add_tpl[i] = tpl1[i] + tpl2[i];
	return (add_tpl);
}

double *sub_tuple(double *tpl1, double* tpl2)
{
	double *sub_tpl;
	int i;

	sub_tpl = (double *)malloc(sizeof(double) * 4);
	if (!sub_tpl)
		return (NULL);
	i = -1;
	while (++i < 4)
		sub_tpl[i] = tpl1[i] - tpl2[i];
	return (sub_tpl);
}

int main()
{
	double *t1 = create_tuple(1, 2, 3, 1);
	double *t2 = create_tuple(2, 3, 4, 1);
	double *t3 = add_tuple(t1, t2);
	double *t4 = scalar_mul_vec(t1, 2);
	double *t5 = scalar_div_vec(t1, 2);
	printf("dot product = %f\n",  dot_product_vec(t1, t2));
	double *t6 = cross_product_vec(t1, t2);
	double *t7 = neg_vec(t1);
	printf("magnitude = %f\n", magnitude_vec(t1));
	double *t8 = normalization_vec(t1, magnitude_vec(t1));

	print_tuple(t4);
	print_tuple(t5);
	print_tuple(t6);
	print_tuple(t7);
	print_tuple(t8);

	free(t1);
	free(t2);
	free(t3);
	free(t4);
	free(t5);
	free(t6);
	free(t7);
	free(t8);
	return (0);
}

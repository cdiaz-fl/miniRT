/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mtx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:19:48 by cdiaz-fl          #+#    #+#             */
/*   Updated: 2022/04/26 08:35:05 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"matrix.h"

#include	<stdlib.h>
#include	<stdio.h>
//Hay que borrar print tuple
void print_tuple(double *tpl)
{
	int i = -1;
	printf("Tuple = ");
	while (++i < 4)
		printf("[%d]%.2f ", i, tpl[i]);
	printf("\n");
}

int main()
{

	t_mtx		mtx;
	double	array[4] = {1.0f, 7.0f, 2.0f, 3.0f};
	double	array2[4] = {5.0f, 4.0f, 2.0f, 2.0f};

	mtx = create_mtx(4);
	init_mtx(&mtx, array, 0);
	init_mtx(&mtx, array, 1);
	init_mtx(&mtx, array, 2);
	init_mtx(&mtx, array, 3);
	print_mtx(&mtx);
	
	t_mtx		mtx2;
	mtx2 = create_mtx(4);
	init_mtx(&mtx2, array2, 0);
	init_mtx(&mtx2, array2, 1);
	init_mtx(&mtx2, array2, 2);
	init_mtx(&mtx2, array2, 3);
	print_mtx(&mtx2);

	//Multiply matrix and matrix
	t_mtx	mtx3;
	mtx3 = mul_mtx(&mtx, &mtx2);
	print_mtx(&mtx3);

	//Multiply matrix and tuple
	double *tup;
	tup = mul_mtx_tup(&mtx, array2);
	print_tuple(tup);


	//Indentity
	t_mtx	mtx4;
	mtx4 = identity_mtx(4);
	print_mtx(&mtx4);

	//Transpose
	t_mtx	mtx5;
	mtx5 = transpose_mtx(&mtx2);
	print_mtx(&mtx5);

	//Invert
	printf("\n...........................Inverting........................\n\n");

			//Detertminant
	t_mtx			mtx_2d;	
	double	array3[2] = {5.0f, 4.0f};
	double	array4[2] = {7.0f, -3.0f};

	mtx_2d = create_mtx(2);
	init_mtx(&mtx_2d, array3, 0);
	init_mtx(&mtx_2d, array4, 1);
	print_mtx(&mtx_2d);
	printf("The determinant is... %.2f\n", det_2d_mtx(&mtx_2d));
	

		//Sub matrix

	t_mtx	mtx6;
	double	array5[4] = {-5.0f, 2.0f, 6.0f, -8.0f};
	double	array6[4] = {1.0f, -5.0f, 1.0f, 8.0f};
	double	array7[4] = {7.0f, 7.0f, -6.0f, -7.0f};
	double	array8[4] = {1.0f, -3.0f, 7.0f, 4.0f};

	mtx6 = create_mtx(3);
	init_mtx(&mtx6, array, 0);
	init_mtx(&mtx6, array2, 1);
	init_mtx(&mtx6, array5, 2);
	print_mtx(&mtx6);

	t_mtx	s_mtx;
	s_mtx = sub_mtx(&mtx6, 0, 1);
	print_mtx(&s_mtx);

		//Minor = Sub matrix + Determinant	
	printf("The 0 1 minor is... %.2f\n", minor_3d_mtx(&mtx6, 0, 1));

		//Cofactor = (+ -) Minor
	printf("The 0 1 minor is... %.2f\n", cofactor_3d_mtx(&mtx6, 0, 1));

	printf("\n...........................Inverting........................\n\n");
		//Any size Determinant Book Example
	printf("Any size determinant\n");
	t_mtx	mtx7;
	double	array9[4] = {-2.0f, -8.0f, 3.0f, 5.0f};
	double	array10[4] = {-3.0f, 1.0f, 7.0f, 3.0f};
	double	array11[4] = {1.0f, 2.0f, -9.0f, 6.0f};
	double	array12[4] = {-6.0f, 7.0f, 7.0f, -9.0f};

	mtx7 = create_mtx(4);
	init_mtx(&mtx7, array9, 0);
	init_mtx(&mtx7, array10, 1);
	init_mtx(&mtx7, array11, 2);
	init_mtx(&mtx7, array12, 3);
	print_mtx(&mtx7);
	printf("The determinant is... %.2f\n", det_mtx(&mtx7));


		//Finally invert
	printf("\n~~~~~~~~~~~~~~~~~~~~~~Finally inverting~~~~~~~~~~~~~~~~~\n\n");
	t_mtx	inverted_mtx;
	t_mtx	mtx8;

	mtx8 = create_mtx(4);
	init_mtx(&mtx8, array5, 0);
	init_mtx(&mtx8, array6, 1);
	init_mtx(&mtx8, array7, 2);
	init_mtx(&mtx8, array8, 3);
	print_mtx(&mtx8);
	printf("The determinant is... %.2f\n", det_mtx(&mtx8));

	inverted_mtx = invert_mtx(&mtx8);
	print_mtx(&inverted_mtx);


	//Free

	free_mtx(&mtx);
	free_mtx(&mtx2);
	free_mtx(&mtx3);	
	free_mtx(&mtx4);
	free_mtx(&mtx5);
	free_mtx(&mtx6);
	free_mtx(&mtx7);
	free_mtx(&mtx8);
	free_mtx(&inverted_mtx);
	free_mtx(&mtx_2d);
	free_mtx(&s_mtx);
	free(tup);
	return 0;
}

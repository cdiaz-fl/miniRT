/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:39:40 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/20 13:51:15 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

/*PRINT TUPLE*/
void	print_tuple(double *tpl); 	//BORRAR

/*CREAR UN PUNTO O VECTOR*/
double	*create_tuple(double x, double y, double z, double w);

/*OPERACIONES ENTRE VECTORES Y PUNTOS*/
double	*add_tuple(double *tpl1, double* tpl2);
double	*sub_tuple(double *tpl1, double* tpl2);

/*OPERACIONES ENTRE VECTORES*/
//vector_operation1
double	*scalar_mul_vec(double *tpl, double scalar);
double	*scalar_div_vec(double *tpl, double scalar);
double	dot_product_vec(double *tpl1, double *tpl2);
double	*cross_product_vec(double *a, double *b);
//vector_operation2
double	*normalization_vec(double *tpl, double magnitude);
double	magnitude_vec(double *tpl);
double	*neg_vec(double *tpl);

#endif

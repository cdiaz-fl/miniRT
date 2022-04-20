/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:39:40 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/20 11:04:27 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

/*PRINT TUPLE*/
void print_tuple(float *tpl); 	//BORRAR

/*CREAR UN PUNTO O VECTOR*/
float *create_tuple(float x, float y, float z, float w);

/*OPERACIONES ENTRE VECTORES Y PUNTOS*/
float *add_tuple(float *tpl1, float* tpl2);
float *sub_tuple(float *tpl1, float* tpl2);

/*OPERACIONES ENTRE VECTORES*/
//vector_operation1
float *scalar_mul_vec(float *tpl, float scalar);
float *scalar_div_vec(float *tpl, float scalar);
float dot_product_vec(float *tpl1, float *tpl2);
float *cross_product_vec(float *a, float *b);
//vector_operation2
float *normalization_vec(float *tpl, float magnitude);
float magnitude_vec(float *tpl);
float *neg_vec(float *tpl);

#endif

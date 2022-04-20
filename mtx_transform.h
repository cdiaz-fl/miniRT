/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_transform.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:12:36 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/20 12:13:06 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MTX_TRANSFORM
# define MTX_TRANSFORM
# define M_PI   3.14159265358979323846264338327950288
//# include "matrix.h" -> Añadir

//mtx_transform.c
float	**translation_mtx(float x, float y, float z);
float	**scaling_mtx(float x, float y, float z);
float	**shearing_mtx(float shear_arr[6]);
//mtx_rotations.c
float	**rotatation_x_mtx(float grade);
float	**rotatation_y_mtx(float grade);
float	**rotatation_z_mtx(float grade);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_transform.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:12:36 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/20 13:48:56 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MTX_TRANSFORM
# define MTX_TRANSFORM
# define M_PI   3.14159265358979323846264338327950288
//# include "matrix.h" -> Añadir

//mtx_transform.c
double	**translation_mtx(double x, double y, double z);
double	**scaling_mtx(double x, double y, double z);
double	**shearing_mtx(double shear_arr[6]);
//mtx_rotations.c
double	**rotatation_x_mtx(double grade);
double	**rotatation_y_mtx(double grade);
double	**rotatation_z_mtx(double grade);

#endif

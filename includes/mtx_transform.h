/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtx_transform.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 11:12:36 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/27 11:29:14 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MTX_TRANSFORM
# define MTX_TRANSFORM
# define M_PI   3.14159265358979323846264338327950288
# include "matrix.h" 

//mtx_transform.c
t_mtx	translation_mtx(double x, double y, double z);
t_mtx	scaling_mtx(double x, double y, double z);
t_mtx	shearing_mtx(double shear_arr[6]);
//mtx_rotations.c
t_mtx	x_rotatation_mtx(double grade);
t_mtx	y_rotatation_mtx(double grade);
t_mtx	z_rotatation_mtx(double grade);

#endif

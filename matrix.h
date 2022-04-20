/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:39:26 by cdiaz-fl          #+#    #+#             */
/*   Updated: 2022/04/20 12:14:45 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MATRIX_H
# define	MATRIX_H

void		print_mtx(float **mtx);
void		init_mtx(float **mtx, float one, float two, float three, float four);
float		**mul_mtx(float **mtx1, float **mtx2);
float   *mul_mtx_tup(float **mtx, float *tup);

float		**create_mtx(void);
void		free_mtx(float **mtx);

#endif

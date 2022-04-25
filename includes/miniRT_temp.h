/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_temp.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:52:36 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/25 12:38:37 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TEMP_H
#define MINIRT_TEMP_H

#include "point_vector.h"
#include "intersections.h"
#include "mlx_utils.h"
#include "get_next_line.h"
#include "../lib/libft/libft.h"
#include "../lib/mlx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_mtx{

    double **data;
    int     size;
}t_mtx;

t_mtx       create_mtx(void);
t_mtx		identity_mtx(unsigned int i);
t_mtx		mul_mtx(t_mtx mtx1, t_mtx mtx2);



#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prueba.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:36:28 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/26 12:34:32 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int main()
{
    t_mlx   mlx;

/*	printf("Transform Ray\n");
	t_ray	r;
	t_mtx	m;
	r = create_ray(create_point(1, 2, 3), create_vect(0, 1, 0));
	m = scaling_mtx(2, 3, 4);
	t_ray	r2 = transform_ray(r, m);
	print_point(r2.origin);
	print_vect(r2.direction);*/
    
	
	mlx_utils_init(&mlx);
    mlx_event(&mlx);
    draw(&mlx);
    mlx_loop(mlx.mlx);

    return (0);
}

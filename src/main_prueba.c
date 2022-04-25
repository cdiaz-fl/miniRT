/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prueba.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:36:28 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/25 11:38:02 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_temp.h"

int main()
{
    t_mlx   mlx;
	
	printf("W-> %d, H -> %d\n", WIDTH, HEIGHT);
    mlx_utils_init(&mlx);
   	mlx_event(&mlx);
    draw(&mlx);
    mlx_loop(mlx.mlx);


/*	printf("Ray equations \n");
	t_point origin = create_point(2, 3, 4);
	t_vect	direction = create_vect(1, 0, 0);
	t_ray	ray = create_ray(origin, direction);
	printf("ray.origin ==" );
	print_point(ray.origin);
	printf("ray.direction ==" );
   	print_vect(ray.direction);

	print_point(position_ray(ray, 2.5));

	printf("\nIntersection Ray with Sphere\n");
	t_ray		ray2 = create_ray(create_point(0, 0, -5), create_vect(0, 0, 1));
	t_sphere	s;
	t_inter inter = intersect_ray(ray2, s);

	printf("count -> %d, p1 -> %f, p2 -> %f\n", inter.count, inter.point[0], inter.point[1]);*/
    return (0);
}

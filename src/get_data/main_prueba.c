/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prueba.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:36:28 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/05 13:37:00 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int main()
{

/*	printf("Transform Ray\n");
	t_ray	r;
	t_mtx	m;
	r = create_ray(create_point(1, 2, 3), create_vect(0, 1, 0));
	m = scaling_mtx(2, 3, 4);
	t_ray	r2 = transform_ray(r, m);
	print_point(r2.origin);
	print_vect(r2.direction);*/

/*	printf("Reflect and normal vect\n");
 	t_sphere	s;
	s.transform = identity_mtx(4);
	s.transform = set_transform_sp(s, scaling_mtx(0.3, 0.8, 1));
	s.inverse = invert_mtx(&s.transform);
	s.transpose = transpose_mtx(&s.inverse);
 	t_vect normal1 = normal_sphere(s, create_point(1, 1, 10));
    print_vect(normal1);
    print_vect(reflect_vect(create_vect(2, 3, 2), normal1));
	*/
/*	printf("Convert color 255 -> hexadecimal\n");
	t_color c_255 = create_color(1, 0, 0);
	printf("Color Int %d\n", convert_color_to_int(c_255));
	
	printf("Scaling : \n");
	t_point	ps = create_point(-4,6,8);
	t_vect vs = create_vect(-4,6,8);
	t_mtx	ms = scaling_mtx(2, 3, 4);
	t_vect	ps2 = mul_vect_mtx(&ms, vs);
	print_vect(ps2);
	t_mtx minve = invert_mtx(&ms);
	t_vect vs2 = mul_vect_mtx(&minve, vs);
	print_vect(vs2);
	printf("\n");
	*/
	{
		t_ray r =  create_ray(create_point(1, 2, 3), create_vect(0, 1, 0));
		t_mtx m = scaling_mtx(2, 3, 4);
	//	t_mtx m = translation_mtx(3, 4, 5);
		t_ray ray_transform =  transform_ray(r, m);
		print_point(ray_transform.origin);
		print_vect(ray_transform.direction);
//Then r2.origin = point(2, 6, 12)
//And r2.direction = vector(0, 3, 0)
		
		t_sphere s;
		t_ray ray = create_ray(create_point(0, 0, -5), create_vect(0, 0, 1));
    //	s.transform = identity_mtx(4);
		//print_mtx(&s.transform);
    //	s.transform = set_transform_sp(s, scaling_mtx(2, 2, 2));
    	s.transform = scaling_mtx(2, 2, 2);
		//print_mtx(&s.transform);
		s.inverse = invert_mtx(&s.transform);
		//print_mtx(&s.inverse);
    	s.transpose = transpose_mtx(&s.inverse);
		//print_mtx(&s.transpose);
		t_inter xs = intersect_ray(ray, s);
		if (xs.count > 0)
		{
			printf("xs.point[0] -> %f\n", xs.point[0]);
			printf("xs.point[1] -> %f\n", xs.point[1]);
		}
	}
/*
	printf("Rotating: \n");
	t_point	p = create_point(0,1,0);
	t_mtx	half = x_rotatation_mtx(45);
	half = invert_mtx(&half);
	t_point	p2 = mul_point_mtx(&half, p);
	print_point(p2);
	printf("\n");

	printf("Normal: \n");
   	t_sphere s;
    s.transform = identity_mtx(4);
	s.transform = set_transform_sp(s, translation_mtx(0, 1, 0));
    s.inverse = invert_mtx(&s.transform);
    s.transpose = transpose_mtx(&s.inverse);

	t_vect	normal_v = get_normal_sphere(s, create_point(0, 1.70711, -0.70711));
	print_vect(normal_v);

   	t_sphere s1;
    s1.transform = identity_mtx(4);
	t_mtx temp1 =  scaling_mtx(1, 0.5, 1);
	t_mtx temp2 =  z_rotatation_mtx(36);
	t_mtx temp3 = mul_mtx(&temp1, &temp2);
	s1.transform = set_transform_sp(s1, temp3);
    s1.inverse = invert_mtx(&s1.transform);
    s1.transpose = transpose_mtx(&s1.inverse);
	t_vect	normal_v2 = get_normal_sphere(s1, create_point(0, 0.70711, -0.70711));
	print_vect(normal_v2);
	printf("\n");
	
	
	printf("Reflect:\n");
	t_vect	reflect_v =	get_reflect_vect(create_vect(1, -1, 0), create_vect(0, 1, 0));
	t_vect	reflect_v2 =get_reflect_vect(create_vect(0, -1, 0), create_vect(0.7071, 0.7071, 0));
	print_vect(reflect_v);
	print_vect(reflect_v2);
	printf("\n");
*/		
/*	printf("Light\n");
	{
   		t_sphere s1;
    	s1.transform = identity_mtx(4);
    	s1.inverse = invert_mtx(&s1.transform);
    	s1.transpose = transpose_mtx(&s1.inverse);

		t_vect	eye_vect = create_vect(0,  0,  -1);
		t_vect	normal_v = create_vect(0, 0, -1);

		t_light2    light;
		light.position = create_point(0, 10, -10);
    	light.brightness = 1;
    	light.intensity = create_color(1, 1, 1);
    
		t_point	world_point = create_point(0, 0, 0);
	
	
		t_color final = lighting(light, s1, world_point, normal_v, create_vect(0, 0, -1));
		printf("color -> %f %f %f\n", final.r, final.g, final.b);
		printf("\n");
	}
*/

	printf("Pintart\n");
    t_mlx   mlx;

	mlx_utils_init(&mlx);
    mlx_event(&mlx);
    draw(&mlx);
    mlx_loop(mlx.mlx);

    return (0);
}

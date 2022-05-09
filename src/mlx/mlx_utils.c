/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 08:36:40 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/06 15:07:16 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void wall_init(t_mlx *mlx)
{
    mlx->wall.width = 0;
    mlx->wall.height = 0;
    mlx->wall.pixel_size_x = WIDTH / 2;
    mlx->wall.pixel_size_y = HEIGHT / 2;
}

static void	window_init(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "MINIRT!");
}

static void	img_init(t_mlx *mlx)
{
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->img.addr = (int *)mlx_get_data_addr(mlx->img.img,
			&mlx->img.bpp, &mlx->img.line_length, &mlx->img.endian);
}

void	mlx_utils_init(t_mlx *mlx)
{
	window_init(mlx);
	img_init(mlx);
	wall_init(mlx);
}

t_color ft_prueba_color(t_sphere s, double min_point, t_ray ray,  int x, int y, t_light light)
{
	//1. Calculamos el punto donde intersecta el rayo con la espfera en el mundo real.
	//Con el vector del rayo y el punto de interscció.
	double z ;

	t_color final = create_color(1, 1, 0);
	if (x == 500 && y == 500)
	{
		z = min_point ;
		printf("Distancia entre el ray.origin y interseccion en el eje z ->  [%f]\n",  min_point);
	}
		t_point world_point2 = add_point_vect(ray.origin, scalar_mul_vect(ray.direction, min_point));
	if (x == 500 && y == 500)
	{
		printf("Intersecion punto mundo REAL: ");
		print_point(world_point2);
		printf("Intersecion punto mundo OBJETO: ");
		t_point object_point = mul_point_mtx(&s.inverse, world_point2);
		print_point(object_point);
	}

	
	//Creamos la luz
	
	t_point world_point = add_point_vect(ray.origin, scalar_mul_vect(ray.direction, min_point));
	t_vect normal_vect = get_normal_sphere(s, world_point);
//	t_vect	ray_vect = create_vect(ray.origin, ray.direction);
	final = lighting(light, s.rgb, world_point, normal_vect, ray.direction);
//	printf("color -> [%f] [%f] [%f]\n", final.r, final.g, final.b);
//	}	

	return (final);
}


void	draw(t_mlx	*mlx)
{
	int x;
	int	y;
	double	world_x;
	double	 world_y;
	double	 world_z = 7;

	t_ray	ray;
	t_point	ray_origin;
	t_point	position;
	t_inter xs;
	t_point center_sphere;

	printf("l -> %d\n", mlx->img.bpp);
	double	wall_size = 7;
	double	pixel_size = wall_size / HEIGHT;
	double	half = wall_size / 2;
	
	t_sphere s;
	s.transform = identity_mtx(4);
//	s.transform = set_transform_sp(s, translation_mtx(0, 0, 3));
//	s.transform = set_transform_sp(s, scaling_mtx(1, 1, 2));
//	t_mtx super_trasn
	s.transform = set_transform_sp(s, scaling_mtx(1, 1, 0.8));
	s.inverse = invert_mtx(&s.transform);
	s.transpose = transpose_mtx(&s.inverse);
	s.rgb = create_color(1, 0, 0);

	t_sphere s2;
	//t_inter	xs2;
	s2.transform = identity_mtx(4);
//	s2.transform = set_transform_sp(s2, translation_mtx(1, 0.2, 1));
	s2.inverse = invert_mtx(&s2.transform);
	ray_origin = create_point(0, 0, -50);
	center_sphere = create_point(0, 0, 0);


	//Create light
	t_light    light;
    light.position = create_point(-10, 10, -10);
    light.brightness = 0.9;
   // light.intensity = create_color(1, 1, 1);
    light.intensity = create_color(1, 1, 1);
	light.ambient  =create_color(0.1, 0.1, 0.1);

	y = -1;
	while (++y < HEIGHT -1)
	{
		x = -1;
		world_y = half - (y * pixel_size);
		while (++x < WIDTH - 1)
		{
		//	if (x == 500 && y == 500)
		//	{
			world_x = (-1 * half) + (x * pixel_size);
			static int i;
			if (i < 3)
			{
		//		printf("%d punto en la pantalla\n", i);
				print_point(create_point(world_x, world_y, world_z));
				i++;
			}
			position = create_point(world_x, world_y, world_z);
			ray = create_ray(ray_origin, normalization_vect(sub_point_point(position, ray_origin)));
			//Aqui habria que calcular todas las intersecciones en una sola funcion
			xs = intersect_ray_sph(ray, s);
//			xs2 = intersect_ray(ray, s2);
			if (xs.count > 0) 
			{
				t_color final = ft_prueba_color(s, xs.min_point, ray, x, y, light);
				mlx->img.addr[y * WIDTH + x] = convert_color_to_int(final);
//				mlx->img.addr[y * WIDTH + x] = convert_color_to_int(create_color(0, 255, 0));
			}
			else
				mlx->img.addr[y * WIDTH + x] = 0x000000;
		//	}
			//if (xs2.count > 0) 
			//	mlx->img.addr[y * WIDTH + x] = 0xFF0000;
		}
	}
	printf("fin\n");;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

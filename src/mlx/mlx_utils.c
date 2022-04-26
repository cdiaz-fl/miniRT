/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 08:36:40 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/26 13:20:53 by zcanales         ###   ########.fr       */
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


void	draw(t_mlx	*mlx)
{
	int x;
	int	y;
	double	world_x;
	double	 world_y;
	double	 world_z = 10;

	t_ray	ray;
	t_point	ray_origin;
	t_point	position;
	t_inter xs;
	t_point center_sphere;

	double	wall_size = 7;
	double	pixel_size = wall_size / HEIGHT;
	double	half = wall_size / 2;
	
	t_sphere s;
	s.transform = identity_mtx(4);
//	s.transform = set_transform_sp(s, scaling_mtx(0.3, 0.8, 1));
//	t_mtx super_trasn
	s.transform = set_transform_sp(s, scaling_mtx(0.3, 0.8, 1));
	s.inverse = invert_mtx(&s.transform);
	
	t_sphere s2;
	t_inter	xs2;
	s2.transform = identity_mtx(4);
	s2.transform = set_transform_sp(s2, translation_mtx(1, 0.2, 1));
	s2.inverse = invert_mtx(&s2.transform);
	
	ray_origin = create_point(0, 0, -5);
	center_sphere = create_point(0, 0, 0);
	y = -1;
	while (++y < HEIGHT -1)
	{
		x = -1;
		world_y = half - (y * pixel_size);
		printf("world_y -> %f\n", world_y);
		while (++x < WIDTH - 1)
		{
			world_x = (-1 * half) + (x * pixel_size);
			position = create_point(world_x, world_y, world_z);
			ray = create_ray(ray_origin, normalization_vect(sub_point_point(position, ray_origin)));
			//Aqui habria que calcular todas las intersecciones en una sola funcion
			xs = intersect_ray(ray, s);
			xs2 = intersect_ray(ray, s2);
			if (xs.count > 0) 
				mlx->img.addr[x * WIDTH + y] = 0xFF00FF;
			if (xs2.count > 0) 
				mlx->img.addr[x * WIDTH + y] = 0xFF0000;
		}
	}
	printf("fin\n");;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

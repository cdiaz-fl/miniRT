/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 08:36:40 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/26 09:11:11 by cdiaz-fl         ###   ########.fr       */
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
	int i;
	int	j;
	t_ray	ray;
	t_point	ray_origin;
	t_point	position;
	t_inter xs;
	
	t_sphere s;
//	s.tranform = identity_matrix;
	ray_origin = create_point(0, 0, 0);
	i = -1;
	while (++i < WIDTH -1)
	{
		j = -1;
		while (++j < HEIGHT - 1)
		{
			position = create_point(i, j, 10);
			ray = create_ray(ray_origin, normalization_vect(sub_point_point(position, ray_origin)));
			xs = intersect_ray(ray, s);
			printf("xs-> %d\n", xs.count);
			if (xs.count > 0) 
				mlx->img.addr[j * WIDTH + i] = 0xFF00FF;
		}
	}
	printf("fin\n");;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

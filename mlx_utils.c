/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 08:36:40 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/22 09:26:09 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_utils.h"

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

	i = -1;
	while (++i < WIDTH -1)
	{
		j = -1;
		while (++j < HEIGHT - 1)
			mlx->img.addr[j * WIDTH + i] = 0xFF00FF;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}


int main()
{
	t_mlx	mlx;

	mlx_utils_init(&mlx);
	mlx_event(&mlx);
/*	window_init(&mlx);
	img_init(&mlx);
	wall_init(&mlx);*/
	draw(&mlx);
	mlx_loop(mlx.mlx);
	return (0);
}

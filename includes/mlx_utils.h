/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 08:24:22 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/27 08:25:19 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MLX_UTILS_H
# define MLX_UTILS_H
# include "../lib/mlx/mlx.h"
# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_wall
{
	int		width;	
	int		height;
	double	pixel_size_x;
	double	pixel_size_y;
}t_wall;

typedef struct s_img
{
	//DATA
	void	*img;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;

}t_img;

typedef struct s_mlx
{
	void    *mlx;
	void    *win;
	
	//IMAGE
	t_img	img;

	//WALL
	t_wall	wall;
}t_mlx;

/*INIT*/
void	mlx_utils_init(t_mlx *mlx);
void	draw(t_mlx  *mlx);
/*EVENTS*/
void	mlx_event(t_mlx *mlx);

#endif

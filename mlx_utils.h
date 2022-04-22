/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 08:24:22 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/22 09:26:07 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MLX_UTILS_H
# define MLX_UTILS_H
# include "mlx/mlx.h"
# define WIDTH 1000
# define HEIGHT 1000
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

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

/*EVENTS*/
void	mlx_event(t_mlx *mlx);

#endif

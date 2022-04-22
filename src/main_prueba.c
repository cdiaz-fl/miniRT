/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prueba.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:36:28 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/22 12:40:45 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT_temp.h"

int main()
{
    t_mlx   mlx;

    mlx_utils_init(&mlx);
    mlx_event(&mlx);
    draw(&mlx);
    mlx_loop(mlx.mlx);

    return (0);
}

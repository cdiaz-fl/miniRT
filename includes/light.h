/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:44:32 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/02 09:49:52 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
#define LIGHT_H
# include "miniRT.h"
#include "math.h"
# define BLACK 0x000000

typedef struct	s_color
{
	double	r;
	double	g;
	double	b;
}t_color;

typedef struct	s_light2
{
	t_color diffuse;
	t_color ambient;
	t_color	specular;

	t_point	position;

	t_color	intensity; // color = (1, 1, 1) * brightness -> blanco * brightnees
	double		brightness;
}t_light2;


//COLOR.c -> Funciones con la estrucutra color.
t_color	create_color(double red, double green, double blue);
t_color	scalar_mul_color(t_color color, double scalar);
t_color mul_color_color(t_color c1, t_color c2); //Igual no hace falta
t_color add_color_color(t_color c1, t_color c2);
void	check_color_range(t_color c);
int		convert_color_to_int(t_color c);
void	check_max_color(t_color *c);

//LIGHT.c -> Calcular color teniendo en cuanta la luz
t_vect  get_normal_sphere(t_sphere s, t_point p);
t_vect	get_reflect_vect(t_vect light_vect, t_vect normal_vect);
t_color	lighting(t_light light, t_point world_point, t_vect normal_vect, t_vect ray_vect);
t_color  lighting2(t_light2 light,t_sphere s, t_point world_point, t_vect normal_vect, t_vect ray_vect);

//COLOR_AT -> Agrupar todas las funciones para calcular el color en un punto
t_color color_at(t_world world, t_ray rsy);
#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:56:10 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/21 15:19:15 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTION.H
#define INTERSECTION.H

#include "point_vector.h"
g
typedef struct s_intersection
{
	char	obj; //Objeto con el que intersecta
	int		nbr_inter;	//Cantidad de intersecciones 
	double	point[2]; //Puntos en el que intersecta con el objeto.
}t_intersec;

typedef struct s_ray
{
	double	origin; //Origin of the point
	double	direction; //Direction of the point 
}t_ray;

//Borrar, ya esta en el object.h
typedef struct s_sphere
{
	//Ahora se asume que x, y, z = 0 y diameter = 1
	double	x;	//El punto describe el centro de la esfera
	double	y;
	double	z;

	double	diameter;

	int	r;	//[0 - 255]
	int	g;
	int	b;
}t_sphere;

/*Crear rayos*/
//Calcular la posicion de un punto determinado del rayo en el plano 3d.
t_point position_ray(t_ray ray, double move);

/*Intersecting Rays with Spheres*/
//1. Calculamos el valor de discriminant
//Nos indica si el rayo intersecta con la esfera.
//Si es negativo -> no hay interseccion
double     discriminat_ray(t_ray ray, t_sphere s, a, b);

//2. Con el valor de discriminat calculamos en que puntos intersecta el rayo
//con el objeto. Devuelve dos puntos. Si tiene el mimso valor, quiere decir
//que intersecta una única vez.
t_intersec *intersect_ray(t_ray ray, t_sphere s);

/*Tracking Intersections*/
//SIN HACER -> Funciones que te agura las intersecciones
//La hacemos?
//t_interGroup inter_group(t_inter t1, t_inter t2);


/*Identifying Hits*/


#endif

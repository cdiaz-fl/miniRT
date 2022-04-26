/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:56:10 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/26 12:34:30 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include "point_vector.h"
#include "objects.h"
typedef struct s_intersection
{
	char					obj; //Objeto con el que intersecta
	int						count;	//Cantidad de intersecciones 
	double					point[2]; //Puntos en el que intersecta con el objeto.
	double					min_point;
	struct s_intersection	*next;
}t_inter;

typedef struct s_ray
{
	t_point	origin; //Origin of the point
	t_vect	direction; //Direction of the point 
}t_ray;

//Borrar, ya esta en el object.h
/*typedef struct s_sphere
{
	//Ahora se asume que x, y, z = 0 y diameter = 1
	double	x;	//El punto describe el centro de la esfera
	double	y;
	double	z;

	double	diameter;

	int	r;	//[0 - 255]
	int	g;
	int	b;
}t_sphere;*/

/*RAY.C*/
/*Crear rayos*/
t_ray	create_ray(t_point p, t_vect v);

//Calcular la posicion de un punto determinado del rayo en el plano 3d.
t_point position_ray(t_ray ray, double move);

//Trasnformar un rayo
t_ray	transform_ray(t_ray r, t_mtx transform);


/*INTERSECTIONS.C*/
/*Intersecting Rays with Spheres*/
//1. Calculamos el valor de discriminant
//Nos indica si el rayo intersecta con la esfera.
//Si es negativo -> no hay interseccion
double     discriminat_ray(t_ray ray, t_sphere s, double *a, double *b);

//2. Con el valor de discriminat calculamos en que puntos intersecta el rayo
//con el objeto. Devuelve dos puntos. Si tiene el mimso valor, quiere decir
//que intersecta una única vez.
t_inter intersect_ray(t_ray ray, t_sphere s);

//Como intersecta en 2 puntos, no intersa en el que esta mas cerca y no sea negativo.
double  get_minpoint(double t1, double t2);

/*Tracking Intersections*/
//SIN HACER -> Funciones que te agura las intersecciones
//La hacemos?
//t_interGroup inter_group(t_inter t1, t_inter t2);

/*Create a list of intersections*/
//MALLOC
t_inter	*create_interlst(t_inter temp);
void		add_intersection(t_inter **head, t_inter *new);

/*Identifying Hits*/
t_inter *get_hit(t_inter *lst);

//Modificar la matriz de la esfera
t_mtx	set_transform_sp(t_sphere s, t_mtx m);
#endif

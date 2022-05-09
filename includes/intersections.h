/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:56:10 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/09 10:31:59 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include "point_vector.h"
#include "objects.h"
typedef struct s_intersection
{
	char					obj_type; //Objeto con el que intersecta
	void					*object;
	int						count;	//Cantidad de intersecciones 
	double					point[2]; //Puntos en el que intersecta con el objeto.
	double					min_point;
	struct s_intersection	*next;
}t_inter;

typedef struct s_ray
{
	t_point	origin; 	//Origin of the point
	t_vect	direction; 	//Direction of the point 
}t_ray;

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
double     discriminat_ray_sp(t_ray ray, t_mtx invert, double *a, double *b);
double     discriminat_ray_cy(t_ray ray, t_mtx invert, double *a, double *b);
//2. Con el valor de discriminat calculamos en que puntos intersecta el rayo
//con el objeto. Devuelve dos puntos. Si tiene el mimso valor, quiere decir
//que intersecta una única vez.
t_inter intersect_ray_sph(t_ray ray, t_sphere s);
t_inter intersect_ray_pln(t_ray ray, t_plane p);
t_inter intersect_ray_cyl(t_ray ray, t_cylinder c);

//Como intersecta en 2 puntos, no intersa en el que esta mas cerca y no sea negativo.
double  get_minpoint(double t1, double t2);


/*Create a list of intersections*/
//MALLOC
t_inter	*create_interlst(t_inter temp);
void		add_intersection(t_inter **head, t_inter *new);

/*Identifying Hits*/
t_inter *get_hit(t_inter *lst);

//Modificar la matriz de la esfera
t_mtx	set_transform_sp(t_sphere s, t_mtx m);
t_mtx	set_transform_mtx(t_mtx before, t_mtx m);
#endif

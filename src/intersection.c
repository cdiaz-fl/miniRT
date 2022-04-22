/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:03:52 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/22 12:40:43 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/intersections.h"
#include <math.h>
t_ray	create_ray(t_point p, t_vect v)
{
	t_ray r;

	r.origin = p;
	r.direction = v;
	return (r);
}

//Esta funcion se usara en el cap 6. Para las luces
//Calcular la posicion de un punto determinado del rayo en el plano 3d.
t_point position_ray(t_ray ray, double move)
{
	t_point new_point;
	t_vect	temp_vect;

	temp_vect = scalar_mul_vect(ray.direction, move);
	new_point = add_point_vect(ray.origin, temp_vect);
	return (new_point);
}

double	get_minpoint(double t1, double t2)
{

	if (t1 < 0 || t2 < 0)
	{
		if (t1 > 0)
			return (t1);
		else if (t2 > 0)
			return (t2);
		else
			return (t1);
	}
	if (t1 > t2)
		return (t1);
	else
		return (t2);

}


//En vez de que devuelva un t_intertesec, se le puede pasar uno y que lo relleno
t_inter intersect_ray(t_ray ray, t_sphere s)
{
	double 		discriminant;
	double 		a;
	double		 b;
	t_inter		inter;
	
	a = 0;
	b = 0;
	//He pasado puntero porque necesitos el valor de a y b para calcular el punto
	//de intersección
	discriminant = discriminat_ray(ray, s, &a, &b);
	inter.obj = 's';
	//Es mejor tener guardados los puntos aunque sean negativos, para hacer laas reflectio y refraction.
	//Aunque eso solo se para el bonus
/*	if (discriminant < 0) //Si discriminat es negativo, no intersecta.
	{
		inter->count = 0;
		return (NULL);
	}*/
	inter.point[0] = ((b * (-1) - sqrt(discriminant))  / (2 * a));
	inter.point[1] = ((b * (-1) + sqrt(discriminant)) / (2 * a));
	inter.min_point = get_minpoint(inter.point[0], inter.point[1]);
	if (discriminant == 0)
		inter.count = 1;
	else if (discriminant < 0)
		inter.count = 0;
	else
		inter.count = 2;
	return (inter);
}

double     discriminat_ray(t_ray ray, t_sphere s, double *a, double *b)
{
	t_vect	sphere_to_ray;
	t_point	origin_point;
	double	c;
	double	**invert_matrix;
	
	
	//1. Invert matrix of sphere
//	invert_matrix = inverse(sphere.tranform);
	
	//2. Tranform matrix of sphere
//	transform_vect(rayv, invert_matrix);
	
	//3. Crear un vector desde el origin point al rayo.
		//Hemos supesto que el diametro de la esferea es 1 y esta ubicada en el punto 0, 0, 0. 
		//Supongo que si luego lo cambiamos tendremos que modificar esto.	
	origin_point = create_point(0, 0, 0);
	sphere_to_ray = sub_point_point(ray.origin, origin_point);

	//4. Calcular los parametros a, b, y c para savar el discriminant.
	(*a) = dot_product_vect(ray.direction, ray.direction);
	(*b) = 2 *  dot_product_vect(ray.direction, sphere_to_ray);
	c = dot_product_vect(sphere_to_ray, sphere_to_ray);
	
	return (((*b) * (*b)) - (4 * (*a) * c));
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:03:52 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/21 14:13:18 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersection.h"
#include <math.h>

//Esta funcion se usara en el cap 6. Para las luces
//Calcular la posicion de un punto determinado del rayo en el plano 3d.
t_point position_ray(t_ray ray, double move)
{
	t_point new_point;
	t_vect	temp_vect;

	temp_vect = scalar_mul_vect(ray.direction, move);
	new_point = add_vect_point(ray.origin, temp_vect);
	return (new_point);
}

//En vez de que devuelva un t_intertesec, se loe puede pasar uno y que lo relleno
t_intersec *intersect_ray(t_ray ray, t_sphere s)
{
	double 		discriminat;
	double 		a;
	double		 b;
	t_intersec	inter;
	
	a = 0;
	b = 0;
	//He pasado puntero porque necesitos el valor de a y b para calcular el punto
	//de intersección
	discriminat = discriminat_ray(ray, sphere_to_ray, &a, &b);
	//Poner ft_calloc
	inter = calloc(sizeof(t_intersec), 0);
	if (!inter)
		return (NULL);
	inter->obj = 's';
	if (discriminat < 0) //Si discriminat es negativo, no intersecta.
	{
		inter->count = 0;
		return (NULL);
	}
	inter->point[0] = ((b * (-1) - sqrt(discriminat)) (2 * a))
	inter->point[1] = ((b * (-1) + sqrt(discriminat)) (2 * a))
	inter->count = 2;
	return (inter);
}

double     discriminat_ray(t_ray ray, t_sphere s, a, b)
{
	t_vect	sphere_to_ray;
	t_point	origin_point;
	double	c;

	//Hemos supesto que el diametro de la esferea es 1 y esta
	//ubicada en el punto 0, 0, 0. 
	//Supongo que si luego lo cambiamos tendremos que modificar esto.	
	origin_point = create_point(0, 0, 0);
	sphere_to_ray = sub_point_point(ray.origin, origin_point);
	(*a) = dot_product_vect(ray.direction, ray.direction);
	(*b) = 2 *  dot_product_vec(ray.direction, sphere_to_ray);
	c = dot_product_vec(sphere_to_ray, sphere_to_ray);
	return (((*b) * (*b)) - (4 * (*a) * c))
}


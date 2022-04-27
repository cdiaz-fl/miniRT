/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:03:52 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/27 16:16:25 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
#include <math.h>

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
		return (t2);
	else
		return (t1);
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
	t_mtx	inverted_matrix;
	t_ray	ray_transform;
	
	//1. Invert matrix of sphere
//	inverted_matrix = invert_mtx(&s.transform);
//	printf("s. -> %f\n", inverted_matrix.data[0][0]);
	
	//2. Tranform matrix of sphere
	ray_transform =  transform_ray(ray, s.inverse);
	
	//3. Crear un vector desde el origin point al rayo.
		//Hemos supesto que el diametro de la esferea es 1 y esta ubicada en el punto 0, 0, 0. 
		//Supongo que si luego lo cambiamos tendremos que modificar esto.	
	origin_point = create_point(0, 0, 0);
	sphere_to_ray = sub_point_point(ray_transform.origin, origin_point);

	//4. Calcular los parametros a, b, y c para savar el discriminant.
	(*a) = dot_product_vect(ray_transform.direction, ray_transform.direction);
	(*b) = 2 *  dot_product_vect(ray.direction, sphere_to_ray);
	c = dot_product_vect(sphere_to_ray, sphere_to_ray) -1;
	return (((*b) * (*b)) - (4 * (*a) * c));
}

//Transformat la matrix de la esfera
t_mtx	set_transform_sp(t_sphere s, t_mtx m)
{
	t_mtx	tmp;
	//print_mtx(&m);
	tmp = mul_mtx(&s.transform, &m);
	//Frea la matriz de la esfera
	return (tmp);
}

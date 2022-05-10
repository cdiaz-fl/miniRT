/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:03:52 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/10 12:53:57 by cdiaz-fl         ###   ########.fr       */
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

t_inter intersect_ray_sph(t_ray ray, t_sphere s)
{
	double 		discriminant;
	double 		a;
	double		 b;
	t_inter		inter;
	
	a = 0;
	b = 0;
	discriminant = discriminat_ray_sp(ray, s.inverse, &a, &b);
	inter.obj_type = 's';
	inter.point[0] = (((b * (-1)) - sqrt(discriminant))  / (2 * a));
	inter.point[1] = (((b * (-1)) + sqrt(discriminant)) / (2 * a));
	inter.min_point = get_minpoint(inter.point[0], inter.point[1]);
	if (discriminant == 0)
		inter.count = 1;
	else if (discriminant < 0)
		inter.count = 0;
	else
		inter.count = 2;
	return (inter);
}

t_inter intersect_ray_pln(t_ray ray, t_plane p)
{
	t_inter		inter;
	double		angle;

	inter.obj_type = 'p';
	angle = dot_product_vect(p.n_vec, ray.direction);
	t_ray ray_transform =  transform_ray(ray, p.inverse);
	if (ray_transform.direction.y > EPSILON)
	{
		inter.count = 1;
		inter.min_point =  ray_transform.origin.y / ray_transform.direction.y * -1;
	//	if (inter.min_point > 0)
			//printf("min_poin -> %f\n", inter.min_point);
		return (inter);
	}
	/*if (angle > EPSILON)
	{
		inter.count = 1;
		inter.min_point = dot_product_vect(sub_point_point(p.pos, ray.origin), p.n_vec) / angle;
		if (inter.min_point  >= 0)
		{
		//	printf("devuelvo cosas\n");
			return (inter);
		}
	}*/
	inter.count = 0;
	return (inter);
}

static bool	is_inside_tops_cy(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((pow(x, 2) + pow(z, 2)) <= 1)
		return true;
	return false;
}

static void	intersect_tops_cy(t_inter *inter, t_ray ray, t_cylinder c)
{
	double	t;

	if (fabs(ray.direction.y) < EPSILON)
		return ;
	t = (c.min - ray.origin.y) / ray.direction.y;
	if (is_inside_tops_cy(ray, t))
	{
		inter->count++;
	//	inter->point[0] = t;
		inter->point[1] = t;
		
	}
	t = (c.max - ray.origin.y) / ray.direction.y;
	if (is_inside_tops_cy(ray, t))
	{
		inter->count++;
	//	inter->point[0] = t;
		inter->point[1] = t;
	}
}

t_inter intersect_ray_cyl(t_ray ray, t_cylinder c)
{
	double 		discriminant;
	double 		a;
	double		 b;
	t_inter		inter;
	
	a = 0;
	b = 0;
	discriminant = discriminat_ray_cy(ray, c.inverse, &a, &b);
	inter.obj_type = 'c';
	inter.point[0] = (((b * (-1)) - sqrt(discriminant))  / (2 * a));
	inter.point[1] = (((b * (-1)) + sqrt(discriminant)) / (2 * a));
	if (discriminant == 0)
		inter.count = 1;
	if (discriminant < 0)
		inter.count = 0;
	else
		inter.count = 2;
	if (fabs(a) < EPSILON) //ray is parallel to the y axis.
		inter.count = 0;
	double temp;
	if (inter.point[0] > inter.point[1] && inter.point[0] > 0)
	{
		temp = inter.point[0];
		inter.point[0] = inter.point[1];
		inter.point[1] = temp;
	}
	//Esta parte es para cortar el cilindro, lo hacemo mañana
	ray =  transform_ray(ray, c.inverse);
	double y0 = ray.origin.y + inter.point[0] * ray.direction.y;
	if (y0 <= c.min || y0 >= c.max)
	{
		inter.count = 0;
		intersect_tops_cy(&inter, ray, c);
	//	return (inter);
	}
	double y1 = ray.origin.y + inter.point[1] * ray.direction.y;
	if (y1 <= c.min || y1 >= c.max) 
	{	
		inter.count = 0;
		intersect_tops_cy(&inter, ray, c);
	//	return inter;
	}

	//Calcular los hit points en las tapas
	//intersect_tops_cy(&inter, ray, c);
	inter.min_point = get_minpoint(inter.point[0], inter.point[1]);

	return (inter);
}




//discriminat_ray -> Calculamos el valor del dicriminat que nos dirá si el rayo intersecta con la esfera y de ser así a que distancia
//1. Invert matrix of sphere -> Lo hacemos al principio (prepare_object_transformations(&all);),fuera del bucle para que no tarde tanto
//2. Tranformamos el rayo al mundo del objeto. -> tranform_ray
//3. Crear un vector desde el origen de la esfera (0, 0, 0) al punto al rayo. -> sphere_to_ray = sub_point_point
//4. Calcular los parametros a, b, y c para sacar el discriminant.
double     discriminat_ray_sp(t_ray ray, t_mtx invert, double *a, double *b)
{
	t_vect	sphere_to_ray;
	double	c;
	t_ray	ray_transform;

	ray_transform =  transform_ray(ray, invert);
	sphere_to_ray = sub_point_point(ray_transform.origin, create_point(0, 0, 0));
	(*a) = dot_product_vect(ray_transform.direction, ray_transform.direction);
	(*b) = 2 *  dot_product_vect(ray_transform.direction, sphere_to_ray);
	c = dot_product_vect(sphere_to_ray, sphere_to_ray) -1;
	return (((*b) * (*b)) - (4 * (*a) * c));
}

double     discriminat_ray_cy(t_ray ray, t_mtx invert, double *a, double *b)
{
	double	c;
	t_ray	ray_transform;
	
	ray.direction = normalization_vect(ray.direction);	//Mirar donde poner esto
	ray_transform =  transform_ray(ray, invert);
	(*a) = pow(ray_transform.direction.x, 2) + pow(ray_transform.direction.z, 2);
	(*b) = (2 * ray_transform.origin.x * ray_transform.direction.x) + (2 * ray_transform.origin.z * ray_transform.direction.z);
	c = pow(ray_transform.origin.x, 2) + pow(ray_transform.origin.z, 2) - 1;
	return (((*b) * (*b)) - (4 * (*a) * c));
}

//Transformat la matrix de la esfera/
//Frea la matriz de la esfera
t_mtx	set_transform_sp(t_sphere s, t_mtx m)
{
	t_mtx	tmp;
	tmp = mul_mtx(&s.transform, &m);
	free_mtx(&s.transform);
	return (tmp);
}

t_mtx	set_transform_mtx(t_mtx before, t_mtx m)
{
	t_mtx	tmp;
	tmp = mul_mtx(&before, &m);
	free_mtx(&before);
	return (tmp);
}
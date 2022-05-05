/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_vect_operations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 09:52:37 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/05 14:37:12 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/point_vector.h"

void print_point(t_point p)
{
	printf("x->[%.2f] ", p.x);
	printf("y->[%.2f] ", p.y);
	printf("z->[%.2f] ", p.z);
	printf("\n");
}

void print_vect(t_vect v)
{
	printf("x->[%.2f] ", v.x);
	printf("y->[%.2f] ", v.y);
	printf("z->[%.2f] ", v.z);
	printf("\n");
}

t_vect	create_vect(double  x, double y, double z)
{
	t_vect v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_point	create_point(double  x, double y, double z)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

t_vect  add_vect_vect(t_vect v1, t_vect v2)
{
	t_vect v;
	
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_point add_point_vect(t_point p1, t_vect v2)
{
	t_point p;
	
	p.x = p1.x + v2.x;
	p.y = p1.y + v2.y;
	p.z = p1.z + v2.z;
	return (p);
}

t_vect  sub_point_point(t_point p1, t_point p2)
{
	t_vect v;
	
	v.x = p1.x - p2.x;
	v.y = p1.y - p2.y;
	v.z = p1.z - p2.z;
	return (v);
}

t_vect  sub_vect_vect(t_vect v1, t_vect v2)
{
	t_vect v;
	
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
/*	if (v.x < 0.0001)
	 	v.x = 0;
	if (v.y < 0.0001)
	 	v.y = 0;
	if (v.z < 0.0001)
	 	v.z = 0;*/
	return (v);
}

t_point  sub_point_vect(t_point p1, t_vect v2)
{
	t_point p;
	
	p.x = p1.x - v2.x;
	p.y = p1.y - v2.y;
	p.z = p1.z - v2.z;
	return (p);
}
/*
int main()
{
	t_point p1 = create_point(1, 2, 3);
	t_vect v1 = create_vect(2, 3, 4);
	print_point(p1);
	print_vect(v1);

	//Operaciones basicas
	print_point(add_point_vect(p1, v1));
	print_vect(add_vect_vect(v1, v1));
	print_vect(sub_vect_vect(v1, v1));
	print_point(sub_point_vect(p1, v1));
	print_vect(sub_point_point(p1, p1));

	//Divisiones y multiplicaciones	
	print_vect(scalar_mul_vect(v1, 2));
	print_vect(scalar_div_vect(v1, 2));
	printf("dot product = %f\n",  dot_product_vect(v1, v1));
	print_vect(cross_product_vect(v1, v1));

	//Operaciones especiales
	print_vect(neg_vect(v1));
	printf("magnitude = %f\n", magnitude_vect(v1));
	print_vect(normalization_vect(v1));

	return (0);
}*/

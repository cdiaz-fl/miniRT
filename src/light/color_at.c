/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:15:10 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/02 09:49:45 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static t_inter	*intersect_world(t_world world, t_ray ray)
{
	t_inter one_inter;
	t_inter *head;

	*head = NULL;
	//Loop all the spheres
	while (world.sphs->next != NULL)
	{
		one_inter = interset_ray(ray, world.sphere);
		create_interlst(one_inter);
		add_intersection(&head, one_inter)
		world.sphs = world.sphs->next;
	}
	//Loop planes
/*	while (world.plns->next != NULL)
	{
		one_inter = interset_ray(ray, world.sphere);
		create_interlst(one_inter);
		add_intersection(&head, one_inter)
		world.plns = world.plns->next;
	}*/
	//Loop cylindres
/*	while (world.cyls->next != NULL)
	{
		one_inter = interset_ray(ray, world.cyls);
		create_interlst(one_inter);
		add_intersection(&head, one_inter)
		world.cyls = world.cyls->next;
	}*/
	return (head);	
}


static t_comps	prepare_computations(t_inter closest_inter, t_ray ray)
{
	//instantiate a data structure for storing some precomputed values
	t_comps	comps;

	// copy the intersection's properties, for convenience
	comps.t = closest_inter.min_point;
	comps.object = closest_inter.obj;

	//precompute some useful values
	comps.point = add_point_vect(ray.origin, scalar_mul_vect(ray.direction, comps.t));
	comps.eyev = neg_vect(ray.direction);
	//Hacer una funcione que calcule la normal dependiendo del tipo de objeto
	if (comps.obj = 's')
		comps.normal =  get_normal_sphere(comps.object, comps.point);
	if  (dot_product_vect(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = neg_vect(comp.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

static t_color	shade_hit(t_world world, t_comps comps)
{
	return (lighting(comps.object.material, world.light, comps.point, comps.eyev, comps.normalv));
}

t_color	color_at(t_world world, t_ray rsy)
{
	t_inter *record_inter;
	t_inter closest_inter;
	t_comps set_comps;
	t_color final_color;
	
	record_inter = intersect_world(world, ray);
	closest_inter = get_hit(record_inter);
	set_comps = prepare_computations(closest_inter, ray);
	final_color = shade_hit(world, set_comps);
	return (final_color);	
}

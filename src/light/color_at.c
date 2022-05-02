/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:15:10 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/02 14:04:11 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_inter	*intersect_world(t_world *world, t_ray ray)
{
	printf("Dentro a_light%f\n", world->a_light.rate);
	t_inter one_inter;
	t_inter *head;
	int i;

	head = NULL;
	i = 0;
	//Loop all the spheres
	while (world->sphs)
	{
		one_inter = intersect_ray(ray, *world->sphs);
		printf("type -> %c\n", one_inter.obj_type);

		//(t_sphere*)one_inter.object = world->sphs;
		(one_inter.object_s) = (world->sphs);
		add_intersection(&head,create_interlst(one_inter));
		world->sphs = world->sphs->next;
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


t_comps	prepare_computations(t_inter closest_inter, t_ray ray)
{
	//instantiate a data structure for storing some precomputed values
	t_comps	comps;

	// copy the intersection's properties, for convenience
	comps.t = closest_inter.min_point;
	//copy_object();
//	comps.object = closest_inter.obj;

	//precompute some useful values
	comps.point = add_point_vect(ray.origin, scalar_mul_vect(ray.direction, comps.t));
	comps.eyev = neg_vect(ray.direction);
	//Hacer una funcione que calcule la normal dependiendo del tipo de objeto
	if (comps.obj_type == 's')
		comps.normalv =  get_normal_sphere(*(t_sphere *)comps.object, comps.point);
	if  (dot_product_vect(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = neg_vect(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

/*static t_color	shade_hit(t_world world, t_comps comps)
{
	return (lighting(comps.object.material, world.light, comps.point, comps.eyev, comps.normalv));
}*/

t_color	color_at(t_world world, t_ray ray)
{
	t_inter *record_inter;
//	t_inter closest_inter;
//	t_comps set_comps;
	t_color final_color = create_color(0, 0, 0);
	
	record_inter = intersect_world(&world, ray);
//	closest_inter = get_hit(record_inter);
//	set_comps = prepare_computations(closest_inter, ray);
//	final_color = shade_hit(world, set_comps);
	return (final_color);	
}

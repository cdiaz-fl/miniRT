/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:15:10 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/03 15:18:07 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_inter	*intersect_world(t_world **world, t_ray ray, t_sphere **s)
{
//	printf("Dentro a_light%f\n", (*world)->a_light.rate);
	t_inter one_inter;
	t_inter *head;
	t_sphere *temp;

	temp = *s;

	head = NULL;
	//Loop all the spheres
	while (temp != NULL)
	{
		one_inter = intersect_ray(ray, *temp);
		(one_inter.object) = (void*)(temp);
		add_intersection(&head,create_interlst(one_inter));
		temp= temp->next;

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
	comps.object = closest_inter.object;
	comps.obj_type = closest_inter.obj_type;

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

t_color	shade_hit(t_world world, t_comps comps)
{
	return (lighting(world.light,*((t_sphere*)comps.object), comps.point, comps.normalv, neg_vect(comps.eyev)));
}

t_color	color_at(t_world *world, t_ray ray)
{
	t_inter *head_lst;
	t_inter *closest_inter;
	t_comps comps;
	t_color final_color = create_color(1, 1, 1);
	
	head_lst = NULL;	
	closest_inter = NULL;
	head_lst = intersect_world(&world, ray, &world->sphs);
	closest_inter = get_hit(head_lst);
	if (closest_inter->count > 0)
	{
		comps = prepare_computations(*closest_inter, ray);
		final_color = shade_hit(*world, comps);
		//mlx->img.addr[x * WIDTH + y] = convert_color_to_int(final_color);
	}
	return (final_color);	
}

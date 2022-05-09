/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:15:10 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/06 15:07:09 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_inter	*intersect_world(t_ray ray, t_sphere **s, t_plane **p)
{
//	printf("Dentro a_light%f\n", (*world)->a_light.rate);
	t_inter one_inter;
	t_inter *head;
	void *temp;

	temp = (void *)(*s);

	head = NULL;
	//Loop all the spheres
	while (temp != NULL)
	{
		one_inter = intersect_ray_sph(ray, *((t_sphere *)temp));
		(one_inter.object) = temp;
		add_intersection(&head,create_interlst(one_inter));
		temp = ((t_sphere *)temp)->next;
	}
	//Loop planes
	
	temp = (void *)(*p);
	
	while (temp != NULL)
	{
		one_inter = intersect_ray_pln(ray, *((t_plane *)temp));
		(one_inter.object) = temp;
		add_intersection(&head,create_interlst(one_inter));
		temp = ((t_plane *)temp)->next;
	}

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
	if (comps.obj_type == 'p')
		comps.normalv = ((t_plane *)comps.object)->n_vec;
	
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
	bool shadow;
//	shadow = is_shadowed(&world, comps.point);
	shadow = is_shadowed(&world, comps.over_point);
	if (shadow == true)
	{
		return (world.light.ambient);
	}
	if (comps.obj_type == 's')
		return (lighting(world.light, ((t_sphere*)comps.object)->rgb, comps.point, comps.normalv, neg_vect(comps.eyev)));
	if (comps.obj_type == 'p')	
		return (lighting(world.light, ((t_plane*)comps.object)->rgb, comps.point, comps.normalv, neg_vect(comps.eyev)));
	return (create_color(1, 0, 0));
}

t_color	color_at(t_world *world, t_ray ray)
{
	t_inter *head_lst;
	t_inter *closest_inter;
	t_comps comps;
	t_color final_color = create_color(1, 1, 1);
	
	head_lst = NULL;	
	closest_inter = NULL;
	head_lst = intersect_world(ray, &world->sphs, &world->plns);
	closest_inter = get_hit(head_lst);
	if (closest_inter->count > 0)
	{
		comps = prepare_computations(*closest_inter, ray);
		comps.over_point = add_point_vect(comps.point, scalar_mul_vect(comps.normalv, EPSILON));
		final_color = shade_hit(*world, comps);
		//mlx->img.addr[y * WIDTH + x] = convert_color_to_int(final_color);
	}
	return (final_color);	
}

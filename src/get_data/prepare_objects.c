/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 08:58:39 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/12 09:08:49 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void prepare_spheres_transformation(t_world *world)
{
	t_sphere **s_head;
	t_sphere *s;

	s_head = &world->sphs;
	s = *s_head;
	while (s)
	{
		printf("s->diameter %f\n", s->diameter);
		s->transform = identity_mtx(4);
		s->transform = set_transform_mtx(s->transform, translation_mtx(s->pos.x, s->pos.y, s->pos.z));
		if (s->diameter != 1)
			s->transform = set_transform_mtx(s->transform, scaling_mtx(s->diameter, s->diameter, s->diameter));
		s->inverse = invert_mtx(&s->transform);
		s->transpose = transpose_mtx(&s->inverse);
		s = s->next;
	}
}

static void prepare_planes_transformation(t_world *world)
{
	t_plane **p_head;
	t_plane *p;
	p_head = &world->plns;
	p = *p_head;
	while (p)
	{
		//double	angle = dot_product_vect(p->n_vec, create_vect(0, 1, 0));
		p->n_vec = ft_normalization(p->n_vec);
		double angle_x =  90 * p->n_vec.x - 0;
		double angle_y = 90 * p->n_vec.y - 90;
		double angle_z =  90 * p->n_vec.z - 0;
		printf("angle: x(%f), y(%f), z(%f)\n", angle_x, angle_y, angle_z);
		p->transform = identity_mtx(4);
		p->transform = set_transform_mtx(p->transform, translation_mtx(p->pos.x, p->pos.y, p->pos.z));
		p->transform = set_transform_mtx(p->transform, x_rotatation_mtx(angle_x));
		p->transform = set_transform_mtx(p->transform, y_rotatation_mtx(angle_y));
		p->transform = set_transform_mtx(p->transform, z_rotatation_mtx(angle_z));
		p->inverse = invert_mtx(&p->transform);
		p->transpose = transpose_mtx(&p->inverse);
		p = p->next;
	}
}

static void prepare_cylinder_transformation(t_world *world)
{
	t_cylinder **c_head;
	t_cylinder *c;
	
	c_head = &world->cyls;
	c = *c_head;
	while (c)
	{
		c->n_vec = ft_normalization(c->n_vec);
		double angle_x =  90 * c->n_vec.x - 90;
		double angle_y = 90 * c->n_vec.y - 0;
		double angle_z =  90 * c->n_vec.z - 90;
		c->transform = identity_mtx(4);
		c->transform = set_transform_mtx(c->transform, translation_mtx(c->pos.x, c->pos.y, c->pos.z));
		c->transform = set_transform_mtx(c->transform, x_rotatation_mtx(angle_x));
		c->transform = set_transform_mtx(c->transform, y_rotatation_mtx(angle_y));
		c->transform = set_transform_mtx(c->transform, z_rotatation_mtx(angle_z));
		c->transform = set_transform_mtx(c->transform, scaling_mtx(c->diameter, c->diameter, c->diameter));
		c->inverse = invert_mtx(&c->transform);
		c->transpose = transpose_mtx(&c->inverse);
		c->min = c->pos.y - c->height / 2; 
		c->max = c->pos.y + c->height / 2; 
		c = c->next;
	}


}
void	prepare_object_transformations(t_world *world)
{

	prepare_spheres_transformation(world);
	prepare_planes_transformation(world);
	prepare_cylinder_transformation(world);
	world->light.ambient =  scalar_mul_color(world->a_light.rgb, world->a_light.rate);
	world->light.intensity = create_color(world->light.rgb.r, world->light.rgb.g, world->light.rgb.b);
}

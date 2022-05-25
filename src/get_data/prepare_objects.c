/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 08:58:39 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/17 09:41:32 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

static void	prepare_spheres_transformation(t_world *world)
{
	t_sphere	**s_head;
	t_sphere	*s;

	s_head = &world->sphs;
	s = *s_head;
	while (s)
	{
		s->transform = identity_mtx(4);
		s->transform = set_transform_mtx(s->transform,
				translation_mtx(s->pos.x, s->pos.y, s->pos.z));
		if (s->diameter != 1)
			s->transform = set_transform_mtx(s->transform,
					scaling_mtx(s->diameter, s->diameter, s->diameter));
		s->inverse = invert_mtx(&s->transform);
		s->transpose = transpose_mtx(&s->inverse);
		s = s->next;
	}
}

void	get_angle_rotation(double *angle_x, double *angle_z, t_vect n_vec)
{
	if (n_vec.y >= 0)
	{	
		*angle_x = asin(n_vec.z / (fabs(n_vec.z) + fabs(n_vec.y))) * 180 / M_PI;
		*angle_z = (-1) * asin(n_vec.x) * 180 / M_PI;
	}
	else
	{
		*angle_x = 180 - asin(n_vec.z / (fabs(n_vec.z) + fabs(n_vec.y))) * 180 / M_PI;
		*angle_z = (-1) * asin(n_vec.x) * 180 / M_PI;
	}	
}
static void	prepare_planes_transformation(t_world *world)
{
	t_plane	**p_head;
	t_plane	*p;
	double	angle_z;
	double	angle_x;

	p_head = &world->plns;
	p = *p_head;
	while (p)
	{
		p->n_vec = normalization_vect(p->n_vec);
		p->n_vec = neg_vect(p->n_vec);
		get_angle_rotation(&angle_x, &angle_z, p->n_vec);
		printf("angle: x(%f), z(%f)\n", angle_x, angle_z);
		p->transform = set_transform_mtx(p->transform, translation_mtx(p->pos.x, p->pos.y, p->pos.z));
		p->transform = set_transform_mtx(p->transform, x_rotatation_mtx(angle_x));
		p->transform = set_transform_mtx(p->transform, z_rotatation_mtx(angle_z));
		p->inverse = invert_mtx(&p->transform);
		p->transpose = transpose_mtx(&p->inverse);
		p = p->next;
	}
}

static void	prepare_cylinder_transformation(t_world *world)
{
	t_cylinder	**c_head;
	t_cylinder	*c;
	double		angle_x;
	double		angle_z;

	c_head = &world->cyls;
	c = *c_head;
	while (c)
	{
		c->transform = set_transform_mtx(c->transform,
				translation_mtx(c->pos.x, c->pos.y, c->pos.z));
		c->n_vec = normalization_vect(c->n_vec);
		print_vect(c->n_vec);
		get_angle_rotation(&angle_x, &angle_z, c->n_vec);
		printf("angle: x(%f), z(%f)\n", angle_x, angle_z);
		c->transform = set_transform_mtx(c->transform, x_rotatation_mtx(angle_x));
		c->transform = set_transform_mtx(c->transform, z_rotatation_mtx(angle_z));
		c->transform = set_transform_mtx(c->transform, scaling_mtx(c->diameter * 0.5, c->height * 0.5, c->diameter * 0.5));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 08:58:39 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/16 13:55:39 by cdiaz-fl         ###   ########.fr       */
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

t_mtx			normal_rotation_matrix(t_vect normal, char c)
{
	double		angle;
	double		vals[3];
	t_vect		axis;
	t_mtx	rotation;

	rotation = create_mtx(4);

	angle = acos(dot_product_vect(normal, create_vect(0, 1, 0)));
	axis = cross_product_vect(normal, create_vect(0, 1, 0));
	vals[0] = cos(angle);
	vals[1] = sin(angle);
	vals[2] = 1.0 - vals[0];
	rotation.data[0][0] = vals[0] + (pow(axis.x, 2) * vals[2]);
	rotation.data[0][1] = (axis.x * axis.y * vals[2]) - (axis.z * vals[1]);
	rotation.data[0][2] = (axis.x * axis.z * vals[2]) + (axis.y * vals[1]);
	rotation.data[1][0] = (axis.y * axis.x * vals[2]) + (axis.z * vals[1]);
	rotation.data[1][1] = vals[0] + (pow(axis.y, 2) * vals[2]);
	rotation.data[1][2] = (axis.y * axis.z * vals[2]) - (axis.x * vals[1]);
	rotation.data[2][0] = (axis.z * axis.x * vals[2]) - (axis.y * vals[1]);
	rotation.data[2][1] = (axis.z * axis.y * vals[2]) + (axis.x * vals[1]);
	rotation.data[2][2] = vals[0] + (pow(axis.z, 2) * vals[2]);
	rotation.data[3][3] = 1;

//	rotation.data[0][0] *= -1;
//	rotation.data[1][1] *= -1;
//	rotation.data[2][2] *= -1;

	rotation.data[3][0] = 0;
	rotation.data[3][1] = 0;
	rotation.data[3][2] = 0;
	rotation.data[0][3] = 0;
	rotation.data[1][3] = 0;
	rotation.data[2][3] = 0;
	printf("rotationnn\n");
	int i = -1;
	while (++i < 4)
	{
		int j = -1;
		while (++j < 4)
			if (rotation.data[i][j] == -0)
				rotation.data[i][j] = 0;
	}
	//print_mtx(&rotation);
	t_mtx	scale;
	if (c == 'c')
	{
		scale = scaling_mtx(-1.0, 1.0, -1.0);
		rotation = mul_mtx(&scale, &rotation);
	}
	if (c == 'z')
	{
		//printf("--------------------------------------------------------------------\n");
		scale = scaling_mtx(1.0, -1.0, 1.0);
		rotation = mul_mtx(&rotation, &scale);
	}
	return (rotation);
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
		printf("plane\n");
		p->n_vec = normalization_vect(p->n_vec);
//		double angle_x =  90 * p->n_vec.x - 0;
		//double angle_y = 90 * p->n_vec.y - 90;
		//double angle_z =  90 * p->n_vec.z - 0;
		p->transform = identity_mtx(4);
		p->transform = set_transform_mtx(p->transform, translation_mtx(p->pos.x, p->pos.y, p->pos.z));
		p->transform = set_transform_mtx(p->transform, normal_rotation_matrix(p->n_vec, 'p'));
	/*	p->transform = set_transform_mtx(p->transform, x_rotatation_mtx(angle_x));
		p->transform = set_transform_mtx(p->transform, y_rotatation_mtx(angle_y));
		p->transform = set_transform_mtx(p->transform, z_rotatation_mtx(angle_z));*/
		p->inverse = invert_mtx(&p->transform);
		p->transpose = transpose_mtx(&p->inverse);
		p = p->next;
	}
}
static void prepare_cylinder_transformation(t_world *world)
{
	t_cylinder **c_head;
	t_cylinder *c;
	char		ch;
	
	c_head = &world->cyls;
	c = *c_head;
	ch = 'c';
	while (c)
	{
		
		if (c->n_vec.y < 0.0 && c->n_vec.z != 0.0)
		{
			ch = 'z';
			c->n_vec.y *= -1;
		}
		c->n_vec = normalization_vect(c->n_vec);
		//printf("normalizationnnn \n");
		//print_vect(c->n_vec);
		//double angle = dot_product_vect(c->n_vec, create_vect(0,1,0)) * 90;
		/*
		double angle_x =  90 * c->n_vec.x ;
		double angle_y = 90 * c->n_vec.y ;
		double angle_z =  90 * c->n_vec.z ;
		*/
		//printf("angle: x(%f), y(%f), z(%f)\n", angle_x, angle_y, angle_z);
		c->transform = identity_mtx(4);
		print_mtx(&c->transform);
		c->transform = set_transform_mtx(c->transform, translation_mtx(c->pos.x, c->pos.y, c->pos.z));
		print_mtx(&c->transform);
		//c->n_vec.x *= -1;
		c->transform = set_transform_mtx(c->transform, normal_rotation_matrix(c->n_vec));
		c->transform = set_transform_mtx(c->transform, scaling_mtx(c->diameter * 0.5, c->height * 0.5, c->diameter * 0.5));
		print_mtx(&c->transform);
		//t_mtx *m;
		//m = mul_mtx_mtx(x_rotatation_mtx(angle_x), y_rotatation_mtx(angle_y));
		//m = mul_mtx_mtx(m, z_rotatation_mtx(angle_y));
		//c->transform = set_transform_mtx(c->transform, *m);
	//	c->transform = set_transform_mtx(c->transform, x_rotatation_mtx(angle_x));
		//c->transform = set_transform_mtx(c->transform, y_rotatation_mtx(angle_y));
	//	c->transform = set_transform_mtx(c->transform, z_rotatation_mtx(angle_z));
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

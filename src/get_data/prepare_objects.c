/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 08:58:39 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/04 08:59:02 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

//vecN = ((vec-minVec)./(maxVec-minVec) - 0.5 ) *2;


double	min_normalization(t_vect v)
{
	double min = 0;
	
	if (v.x <= v.y)
		min = v.x;
	else
		min = v.y;
	if (v.z <= min)
		min = v.z;
	return (min);
}


double	max_normalization(t_vect v)
{
	double max = 0;

	if (v.x >= v.y)
		max = v.x;
	else
		max = v.y;
	if (v.z >= max)
		max = v.z;
	return (max);
}
/*    % Automated normalization
    if minVec >= 0
        % Normalize between 0 and 1
        vecN = (vec - minVec)./( maxVec - minVec );
        vecD = minVec + vecN.*(maxVec - minVec);
    elseif maxVec <= 0
        % Normalize between -1 and 0
        vecN = (vec - maxVec)./( maxVec - minVec );
        vecD = maxVec + vecN.*(maxVec - minVec);
    else
        % Normalize between -1 and 1
        vecN = ((vec-minVec)./(maxVec-minVec) - 0.5 ) *2;
        vecD = (vecN./2+0.5) * (maxVec-minVec) + minVec;
    end*/
t_vect	ft_normalization(t_vect v)
{
	t_vect normal;
	double	range;
	double min;
	double max;

	min = min_normalization(v);
	max = max_normalization(v);
	range = max - min;
	normal = create_vect(v.x - min, v.y - min, v.z - min);
	if (min >= 0)
		normal = scalar_div_vect(normal, range);
	else if (max <= 0)
	{
		normal = create_vect(v.x - max, v.y - max, v.z - max);
		normal = scalar_div_vect(normal, range);
	}
	else
	{
		normal = scalar_div_vect(normal, range);
		normal.x -= 0.5;
		normal.y -= 0.5;
		normal.z -= 0.5;
		normal = scalar_mul_vect(normal, 2);
	}

	return (normal);
}

void	prepare_object_transformations(t_world *world)
{
	t_sphere **s_head;
	t_sphere *s;

	s_head = &world->sphs;
	s = *s_head;
	while (s)
	{
		printf("s->diameter %f\n", s->diameter);
		s->transform = identity_mtx(4);
		s->transform = set_transform_sp(*s, translation_mtx(s->pos.x, s->pos.y, s->pos.z));
		if (s->diameter != 1)
			s->transform = set_transform_sp(*s, scaling_mtx(s->diameter, s->diameter, s->diameter));
		s->inverse = invert_mtx(&s->transform);
		s->transpose = transpose_mtx(&s->inverse);
		s = s->next;
	}
	world->light.ambient =  scalar_mul_color(world->a_light.rgb, world->a_light.rate);
	world->light.intensity = create_color(world->light.rgb.r, world->light.rgb.g, world->light.rgb.b);
	t_plane **p_head;
	t_plane *p;
	p_head = &world->plns;
	p = *p_head;
	while (p)
	{
		//double	angle = dot_product_vect(p->n_vec, create_vect(0, 1, 0));
		p->n_vec = ft_normalization(p->n_vec);
		printf("VECT\n");
		print_vect(p->n_vec);
		double angle_x =  90 * p->n_vec.x - 0;
		double angle_y = 90 * p->n_vec.y - 90;
		double angle_z =  90 * p->n_vec.z - 0;
		printf("angle: x(%f), y(%f), z(%f)\n", angle_x, angle_y, angle_z);
		print_vect(p->n_vec);
		p->transform = identity_mtx(4);
		p->transform = set_transform_mtx(p->transform, translation_mtx(p->pos.x, p->pos.y, p->pos.z));
		p->transform = set_transform_mtx(p->transform, x_rotatation_mtx(angle_x));
		p->transform = set_transform_mtx(p->transform, y_rotatation_mtx(angle_y));
		p->transform = set_transform_mtx(p->transform, z_rotatation_mtx(angle_z));
		p->inverse = invert_mtx(&p->transform);
		print_mtx(&p->transform);
		print_mtx(&p->inverse);
		//s->transpose = transpose_mtx(&s->inverse);
		p = p->next;
	}
	t_cylinder **c_head;
	t_cylinder *c;
	c_head = &world->cyls;
	c = *c_head;
	while (c)
	{
		//double	angle = dot_product_vect(p->n_vec, create_vect(0, 1, 0));
		print_vect(c->n_vec);
		c->n_vec = ft_normalization(c->n_vec);
		double angle_x =  90 * c->n_vec.x - 90;
		double angle_y = 90 * c->n_vec.y - 0;
		double angle_z =  90 * c->n_vec.z - 90;
		printf("angle: x(%f), y(%f), z(%f)\n", angle_x, angle_y, angle_z);
		c->transform = identity_mtx(4);
		c->transform = set_transform_mtx(c->transform, translation_mtx(c->pos.x, c->pos.y, c->pos.z));
		c->transform = set_transform_mtx(c->transform, x_rotatation_mtx(angle_x));
		c->transform = set_transform_mtx(c->transform, y_rotatation_mtx(angle_y));
		c->transform = set_transform_mtx(c->transform, z_rotatation_mtx(angle_z));
		c->transform = set_transform_mtx(c->transform, scaling_mtx(c->diameter, c->diameter, c->diameter));
		c->inverse = invert_mtx(&c->transform);
		c->transpose = transpose_mtx(&c->inverse);
		//Calcular el min y max para cortar el cilindro. Lo hacemos mañana
		/*c->min =  -1 * c->height / 2 - c->pos.y; 
		c->max = c->height / 2 + c->pos.y;*/  
		c = c->next;
	}
}

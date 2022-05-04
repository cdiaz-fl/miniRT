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

void	prepare_object_transformations(t_world *world)
{
	t_sphere **s_head;
	t_sphere *s;

	s_head = &world->sphs;
	s = *s_head;
	while (s)
	{
		s->transform = identity_mtx(4);
		s->transform = set_transform_sp(*s, translation_mtx(s->pos.x, s->pos.y, s->pos.z));
		if (s->diameter != 1)
			s->transform = set_transform_sp(*s, scaling_mtx(s->diameter, s->diameter, s->diameter));
		s->inverse = invert_mtx(&s->transform);
		s->transpose = transpose_mtx(&s->inverse);
		s = s->next;
	}
	world->light.ambient =  scalar_mul_color(world->a_light.rgb, world->a_light.rate);
	world->light.intensity = create_color(world->light.rgb.r, world->light.rgb.g, world->light.rgb.b);;
}

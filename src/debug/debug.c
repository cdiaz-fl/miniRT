/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 12:37:38 by cdiaz-fl          #+#    #+#             */
/*   Updated: 2022/05/26 08:39:58 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/miniRT.h"
#include	"../../includes/debug.h"

void	print_values(t_world	*all)
{
	t_sphere	*tmp;
	t_plane		*p_tmp;
	t_cylinder	*c_tmp;
	t_sphere	**s_head;
	t_plane		**p_head;
	t_cylinder	**c_head;
	int	i;

	printf("\n\n--------------------  Camera  ---------------------\n");
	printf("|                                                 |\n");
	printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", all->cam.pos.x, all->cam.pos.y, all->cam.pos.z);
	printf("|    nx = %6.2f    ny = %6.2f    nz = %6.2f    |\n", all->cam.n_vec.x, all->cam.n_vec.y, all->cam.n_vec.z);
	printf("|    fov = %6f                                 |\n", all->cam.fov);
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");

	
	printf("\n\n--------------------  ALight  ---------------------\n");
	printf("|                                                 |\n");
	printf("|     rate = %6.2f                               |\n", all->a_light.rate);
	printf("|     R = %6f   G = %6f    B = %6f       |\n", all->a_light.rgb.r, all->a_light.rgb.g, all->a_light.rgb.b);
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");

	printf("\n\n--------------------   Light  ---------------------\n");
	printf("|                                                 |\n");
	printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", all->light.position.x, all->light.position.y, all->light.position.z);
	printf("|     glow = %6.2f                               |\n", all->light.brightness);
	printf("|     R = %6f   G = %6f    B = %6f       |\n", all->light.rgb.r, all->light.rgb.g, all->light.rgb.b);
	printf("|     R = %6f   G = %6f    B = %6f       |\n", all->light.intensity.r, all->light.intensity.g, all->light.intensity.b);
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");

	printf("\n\n--------------------  Sphers  ---------------------\n");
	printf("|                                                 |\n");
	s_head = &all->sphs;
	tmp = *s_head;
	i = 0;
	while (++i && tmp != NULL)
	{
		printf("|      Number = %6d                                   |\n", i);
		printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", tmp->pos.x, tmp->pos.y, tmp->pos.z);
		printf("|     diam = %6.2f                               |\n", tmp->diameter);
		printf("|     R = %6f   G = %6f    B = %6f       |\n", tmp->rgb.r, tmp->rgb.g, tmp->rgb.b);
		tmp = tmp->next;
	}
	printf("---------------------------------------------------\n");

	(void)p_head;
	(void)p_tmp;

	printf("\n\n--------------------  Planes  ---------------------\n");
	printf("|                                                 |\n");
	p_head = &all->plns;
	p_tmp = *p_head;
	i = 0;
	while (++i && p_tmp != NULL)
	{
		printf("|    Number = %6d                                    |\n", i);
		printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", p_tmp->pos.x, p_tmp->pos.y, p_tmp->pos.z);
		printf("|     nx = %6.2f    ny = %6.2f    nz = %6.2f   |\n", p_tmp->n_vec.x, p_tmp->n_vec.y, p_tmp->n_vec.z);
		printf("|     R = %6f   G = %6f    B = %6f       |\n", p_tmp->rgb.r, p_tmp->rgb.g, p_tmp->rgb.b);
		p_tmp = p_tmp->next;
	}
	printf("---------------------------------------------------\n");

	printf("\n\n--------------------  Cylinds ---------------------\n");
	printf("|                                                 |\n");
	c_head = &all->cyls;
	c_tmp = *c_head;
	i = 0;
	while (++i && c_tmp != NULL)
	{
		printf("|     Number = %6d                                    |\n", i);
		printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", c_tmp->pos.x, c_tmp->pos.y, c_tmp->pos.z);
		printf("|     nx = %6.2f    ny = %6.2f    nz = %6.2f   |\n", c_tmp->n_vec.x, c_tmp->n_vec.y, c_tmp->n_vec.z);
		printf("|     diam = %6.2f                               |\n", c_tmp->diameter);
		printf("|     height = %6.2f                             |\n", c_tmp->height);
		printf("|     R = %6f   G = %6f    B = %6f       |\n", c_tmp->rgb.r, c_tmp->rgb.g, c_tmp->rgb.b);
		c_tmp = c_tmp->next;
	}
	printf("---------------------------------------------------\n");
}

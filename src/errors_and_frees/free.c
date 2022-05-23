/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 09:32:06 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/13 09:32:07 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/miniRT.h"

void	free_inter_lst(t_inter *head)
{
	t_inter	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

void	free_2d_array(char **s)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

static void	free_spheres(t_world *w)
{
	t_sphere	*temp_s;

	temp_s = w->sphs;
	while (w->sphs)
	{
		free_mtx(&w->sphs->transform);
		free_mtx(&w->sphs->inverse);
		free_mtx(&w->sphs->transpose);
		w->sphs = w->sphs->next;
		free(temp_s);
		temp_s = w->sphs;
	}
}
static void	free_planes(t_world *w)
{
	t_plane	*temp_p;

	temp_p = w->plns;
	while (w->plns)
	{
		free_mtx(&w->plns->transform);
		free_mtx(&w->plns->inverse);
		free_mtx(&w->plns->transpose);
		w->plns = w->plns->next;
		free(temp_p);
		temp_p = w->plns;
	}
}

static void free_cylinders(t_world *w)
{
	t_cylinder	*temp_c;

	temp_c = w->cyls;
	while (w->cyls)
	{
		free_mtx(&w->cyls->transform);
		free_mtx(&w->cyls->inverse);
		free_mtx(&w->cyls->transpose);
		w->cyls = w->cyls->next;
		free(temp_c);
		temp_c = w->cyls;
	}
}

void	free_structures(t_world *w)
{
	free_spheres(w);
	free_planes(w);
	free_cylinders(w);
}

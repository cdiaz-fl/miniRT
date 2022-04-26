/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:03:52 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/26 09:16:22 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/intersections.h"
#include <math.h>
//ADD una interseccion
void	add_intersection(t_inter **head, t_inter new)
{
	t_inter *temp;
	
	if (*head)
	{
		*head = new;
		return;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
}

//Una rayo puede intersectar con mas de un objeto.
//Por eso creamos una lista de todas los puntos en los que intersecta.
t_inter *create_interlst(t_inter temp)
{
	t_inter *new;

	new = (t_inter)malloc(sizeof(t_inter));
	if (!new)
		return (NULL);
	new->point[0] = temp.point[0];
	new->point[1] = temp.point[1];
	new->min_point = temp.min_point;
	new->count = temp.count;
	new->obj = temp.obj;
	new->next = NULL;
	return (new);
}

//De todos los puento en los que intersecta el rayo con los objetos, solo nos interesa el punto max pequeños 
//siempre que sea positivo
t_inter	*get_hit(t_inter *lst)
{
	t_inter *temp;
	t_inter *min_lst;
	double	min;
	
	temp = lst;
	min_lst = lst;
	min = min_lst->min_point;
	while (temp->next != NULL)
	{
		if (temp->min_point < min && temp->min_point >= 0)
		{
			min = temp->min_point;
			min_lst = temp;
		}
		temp = temp->next;
	}
	return (min_lst);
}

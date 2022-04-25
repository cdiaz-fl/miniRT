/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:43:51 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/25 13:16:24 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//normal_at -> Devuelve la normal en unpunto determinado de una esfera
//PSEUDOCODIGO
//1. Calculamos el vector entre;
//		-El centro de la esfera.
//		-Un punto en la superfici de la esfera.
//2. Lo normalizamos. Porque? A menudo se normaliza un vector porque sólo te importa la dirección a la que apunta el vector y no la magnitud.
//FALTA POR COMPPLETAR EL CAMBIIO DE MUNDOS - > UNA MOVIDA
t_vect	normal_at(t_sphere s, t_point p)
{
	t_vect center_surface_distance;

	center_surface_distance =  sub_point_point(p, create_point(0, 0, 0));
	return (normalization_vect(center_surface_distance));
}

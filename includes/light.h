/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:44:32 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/26 11:36:34 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT.H
#define LIGHT.H

typedef struct s_material
{
	double	ambient;		//	[0.0 - 1.0]
	double	diffuse;		//	[0.0 - 1.0]
	double	specular;		//	[0.0 - 1.0]
	double	shininess;	//	[10.0 - 200.0]  10 = mucha luz    200 = poca luz

}t_material;

t_vect  normal_at(t_sphere s, t_point p);

#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:28:24 by cdiaz-fl          #+#    #+#             */
/*   Updated: 2022/05/02 13:43:38 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	CAMERA_H
# define	CAMERA_H

#include	"matrix.h"
#include	"intersections.h"
#include	"objects.h"

t_mtx	view_transformation(t_point from, t_point to, t_vect up);
void	set_camera(t_camera *cam);
t_ray	ray_for_pixel(t_camera *cam, double px, double py);

#endif

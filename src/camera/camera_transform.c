/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 09:16:10 by cdiaz-fl          #+#    #+#             */
/*   Updated: 2022/05/05 07:39:08 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/miniRT.h"
#include	"../../includes/matrix.h"
#include	<math.h>

t_mtx	view_transformation(t_point from, t_point to, t_vect up)
{
	t_mtx		transform;
	t_mtx		translation;
	t_vect	forward;
	t_vect	left;
	t_vect	true_up;
	double	rows[4][4];


	forward = normalization_vect(sub_point_point(to, from));
	left = cross_product_vect(forward, up);
	true_up = cross_product_vect(left, forward);
	transform = create_mtx(4);
	rows[0][0] = left.x;
	rows[0][1] = left.y;
	rows[0][2] = left.z;
	rows[0][3] = 0;
	rows[1][0] = true_up.x;
	rows[1][1] = true_up.y;
	rows[1][2] = true_up.z;
	rows[1][3] = 0;
	rows[2][0] = forward.x * -1;
	rows[2][1] = forward.y * -1;
	rows[2][2] = forward.z * -1;
	rows[2][3] = 0;
	rows[3][0] = 0;
	rows[3][1] = 0;
	rows[3][2] = 0;
	rows[3][3] = 1;
	init_mtx(&transform, rows[0], 0);
	init_mtx(&transform, rows[1], 1);
	init_mtx(&transform, rows[2], 2);
	init_mtx(&transform, rows[3], 3);
	//print_mtx(&transform);
	translation = identity_mtx(4);
	translation.data[0][3] = from.x * -1;
	translation.data[1][3] = from.y * -1;
	translation.data[2][3] = from.z * -1;
	//print_mtx(&translation);
	transform = mul_mtx(&transform, &translation);
	//print_mtx(&transform);
	return	transform;
}

void	set_camera(t_camera *cam)
{
	double		half_view;
	double		aspect_ratio;

	half_view = tan((cam->FOV * (M_PI / 180)) / 2); //Pasing degrees to radians
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	if (aspect_ratio >= 1)
	{
		cam->half_w = half_view;
		cam->half_h = half_view / aspect_ratio;
	}
	else
	{
		cam->half_w = half_view * aspect_ratio;
		cam->half_h = half_view;
	}
	cam->pix_s = (cam->half_w * 2) / (double)WIDTH;
}


t_ray	ray_for_pixel(t_camera *cam, double px, double py)
{
	t_ray		ray;
	double	xoffset;
	double	yoffset;
	t_point	world_pt;
	t_point	pixel_pt;
	t_mtx		invert;

	xoffset = (px + 0.5) * cam->pix_s;
	yoffset = (py + 0.5) * cam->pix_s;
	world_pt = create_point(cam->half_w - xoffset, cam->half_h - yoffset, -1); //Este -1 es la distancia en z
	pixel_pt = mul_point_mtx(&cam->invert, world_pt);
	ray.origin = mul_point_mtx(&cam->invert, create_point(0, 0, -50));
	ray.direction = normalization_vect(sub_point_point(pixel_pt, ray.origin));
	return ray;
}

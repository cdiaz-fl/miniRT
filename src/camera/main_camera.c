/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:32:58 by cdiaz-fl          #+#    #+#             */
/*   Updated: 2022/05/05 14:37:16 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/miniRT.h"
#include	"../../includes/matrix.h"

int	main()
{
	t_point	from;
	t_point	to;
	t_vect	up;
	t_camera	cam;

	from = create_point(1, 3, 2);
	to = create_point(4, -2, 8);
	up = create_vect(1, 1, 0);

	printf("---------Transformation matrix of the camera---------\n\n");

	cam.transform = view_transformation(from, to, normalization_vect(up));
	print_mtx(&cam.transform);

	printf("\n\n---------Calculating pixel size---------\n\n");

	cam.FOV = 90;
	set_camera(&cam);
	printf("pixel size is = %f\n", cam.pix_s);
	printf("half width is = %f\n", cam.half_w);
	printf("half height is = %f\n", cam.half_h);

	printf("\n\n---------Ray for pixel function---------\n\n");
	cam.transform = y_rotatation_mtx(45);
	t_mtx	translation = translation_mtx(0, -2, 5);
	cam.transform = mul_mtx(&cam.transform, &translation);
//	cam.transform = identity_mtx(4);
	cam.invert = invert_mtx(&cam.transform);
	t_ray	new_ray;
	new_ray = ray_for_pixel(&cam, 100, 50);
	printf("Ray origin is %f, %f, %f\n", new_ray.origin.x, new_ray.origin.y, new_ray.origin.z);
	printf("Ray direction is ");
	print_vect(new_ray.direction);
	return 0;
}

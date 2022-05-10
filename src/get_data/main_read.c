
#include	<fcntl.h>	//Open
#include	<unistd.h>	//Write
#include	"../../includes/miniRT.h"

void	add_walls(t_world *world);
void	add_spheres_list(t_world *all, t_sphere **head);
t_sphere	*get_last_sphere_list(t_sphere **head);

int	is_float(char *s, int *i, int j, int nb)
{
	int	sign;
	int	dot;

	sign = 0;
	dot = 0;
	while(s[++j])
	{
		if (s[j] && (s[j] == '+' || s[j] == '-'))
			sign++;
		if (s[j] >= '0' && s[j] <= '9')
		{
			while(s[j] && s[j] >= '0' && s[j] <= '9' && ++nb)
				j++;
			if (s[j] && s[j] == '.')
				dot++;
			while(s[j] && s[j] >= '0' && s[j] <= '9' && ++nb)
				j++;
			break;
		}
	}
	if (!nb || (nb == 1 && dot))
		return 0;
	*i = j - 1;
	if (s[j] && s[j] == ',')
		*i = j;
//	printf("i -> %d, j -> %d\n", *i, j);
	return 1;
}

int	check_line_syntax(char *s)
{
	int	i;
	int	no_more_char;

	i = -1;
	no_more_char = 0;
	while (s[++i])
	{
		//printf("p -> %c\n", s[i]);
		if (is_float(s, &i, i - 1, 0))
			i++;
		else if (!no_more_char && (ft_strchr("ACL", s[i]) ||
			(s[i] == 's' && s[++i] && s[i] == 'p') ||
			(s[i] == 'p' && s[++i] && s[i] == 'l') ||
			(s[i] == 'c' && s[++i] && s[i] == 'y')))
			no_more_char = 1;
	//	else if (s[i] > 32)
	//		return 1;

	}
	return 0;
}

void	get_values(char *line, t_world *all)
{
	int	i;
	int	out;

	out = 0;
	i = -1;
	while(line[++i])
	{
		if (check_line_syntax(line))
			wrong_values_handling(line, all);
		if (line[i] == 'A' && ++out)
			all->a_light = create_amblight(line);
		if (line[i] == 'C' && ++out)
			all->cam = create_camera(line);
		else if (line[i] == 'L' && ++out)
			all->light = create_light(line);
		else if (line[i] == 'p' && ++out)
			create_planes(line, all);
		else if (line[i] == 's' && ++out)
			create_spheres(line, all);
		else if (line[i] == 'c' && ++out)
			create_cylinders(line, all);
		if (out)
			break ;
		//else if (line[i] > 32) //Es char imprimible
		//	wrong_values_handling(line, all);
	}
}


static int	basic_error_handling(int argc, char **argv)
{
	int	fd;

	if (argc != 2 && write(2, "\e[1;31mError\n", 13))
	{
 		write(2, "Wrong parameters ❌\n", 21);
		exit (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1 && write(2, "\e[1;31mError\n", 13))
	{
 		write(2, "Invalid file ❌\n", 17);
		exit (1);
	}
	return fd;
}

void	print_values(t_world	*all)
{
	t_sphere	*tmp;
	t_plane		*p_tmp;
	t_sphere	**s_head;
	t_plane		**p_head;
//	t_cylinder	*c_tmp;
//	t_cylinder	**c_head;
	int	i;

	printf("\n\n--------------------  Camera  ---------------------\n");
	printf("|                                                 |\n");
	printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", all->cam.pos.x, all->cam.pos.y, all->cam.pos.z);
	printf("|    nx = %6.2f    ny = %6.2f    nz = %6.2f    |\n", all->cam.n_vec.x, all->cam.n_vec.y, all->cam.n_vec.z);
	printf("|    FOV = %6f                                 |\n", all->cam.FOV);
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
	while (++i && tmp->next != NULL)
	{
		printf("|      Number = %6d                                   |\n", i);
		printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", tmp->pos.x, tmp->pos.y, tmp->pos.z);
		printf("|     diam = %6.2f                               |\n", tmp->diameter);
		printf("|     R = %6f   G = %6f    B = %6f       |\n", tmp->rgb.r, tmp->rgb.g, tmp->rgb.b);
		tmp = tmp->next;
	}
	printf("|                                                 |\n");
	printf("|      Number = %d                                 |\n", i);
	printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", tmp->pos.x, tmp->pos.y, tmp->pos.z);
	printf("|     diam = %6.2f                               |\n", tmp->diameter);
	printf("|     R = %6f   G = %6f    B = %6f       |\n", tmp->rgb.r, tmp->rgb.g, tmp->rgb.b);
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");

	(void)p_head;
	(void)p_tmp;

	printf("\n\n--------------------  Planes  ---------------------\n");
	printf("|                                                 |\n");
	p_head = &all->plns;
	p_tmp = *p_head;
	i = 0;
	while (++i && p_tmp->next != NULL)
	{
		printf("|    Number = %6d                                    |\n", i);
		printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", p_tmp->pos.x, p_tmp->pos.y, p_tmp->pos.z);
		printf("|     nx = %6.2f    ny = %6.2f    nz = %6.2f   |\n", p_tmp->n_vec.x, p_tmp->n_vec.y, p_tmp->n_vec.z);
		printf("|     R = %6f   G = %6f    B = %6f       |\n", p_tmp->rgb.r, p_tmp->rgb.g, p_tmp->rgb.b);
		p_tmp = p_tmp->next;
	}
	printf("|                                                 |\n");
	printf("|      Number = %d                                 |\n", i);
	printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", p_tmp->pos.x, p_tmp->pos.y, p_tmp->pos.z);
	printf("|     nx = %6.2f    ny = %6.2f    nz = %6.2f   |\n", p_tmp->n_vec.x, p_tmp->n_vec.y, p_tmp->n_vec.z);
	printf("|     R = %6f   G = %6f    B = %6f       |\n", p_tmp->rgb.r, p_tmp->rgb.g, p_tmp->rgb.b);
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");
/*
	printf("\n\n--------------------  Cylinds ---------------------\n");
	printf("|                                                 |\n");
	c_head = &all->cyls;
	c_tmp = *c_head;
	i = 0;
	while (++i && c_tmp->next != NULL)
	{
		printf("|     Number = %6d                                    |\n", i);
		printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", c_tmp->pos.x, c_tmp->pos.y, c_tmp->pos.z);
		printf("|     nx = %6.2f    ny = %6.2f    nz = %6.2f   |\n", c_tmp->n_vec.x, c_tmp->n_vec.y, c_tmp->n_vec.z);
		printf("|     diam = %6.2f                               |\n", c_tmp->diameter);
		printf("|     height = %6.2f                             |\n", c_tmp->height);
		printf("|     R = %6f   G = %6f    B = %6f       |\n", c_tmp->rgb.r, c_tmp->rgb.g, c_tmp->rgb.b);
		c_tmp = c_tmp->next;
	}
	printf("|                                                 |\n");
	printf("|      Number = %d                                 |\n", i);
	printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", c_tmp->pos.x, c_tmp->pos.y, c_tmp->pos.z);
	printf("|     nx = %6.2f    ny = %6.2f    nz = %6.2f   |\n", c_tmp->n_vec.x, c_tmp->n_vec.y, c_tmp->n_vec.z);
	printf("|     diam = %6.2f                               |\n", c_tmp->diameter);
	printf("|     height = %6.2f                             |\n", c_tmp->height);
	printf("|     R = %6f   G = %6f    B = %6f       |\n", c_tmp->rgb.r, c_tmp->rgb.g, c_tmp->rgb.b);
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");*/
}


void	prueba_default(t_world *world, t_mlx *mlx)
{
	int x;
	int	y;
	double	world_x;
	double	 world_y;
//	double	 world_z = 10;

	t_ray	ray;
//	t_point	ray_origin;
//	t_point	position;
//	ray_origin = create_point(0, 0, -50);
	
	double	wall_size = 7;
	double	pixel_size = wall_size / HEIGHT;
	double	half = wall_size / 2;
	
	
//	ray_origin = create_point(0, 0, -500);
	
/*	printf("specular r[%f], g[%f], b[%f]\n", world->light.specular.r, world->light.specular.g, world->light.specular.b);
	printf("ambient r[%f], g[%f], b[%f]\n", world->light.ambient.r, world->light.ambient.g, world->light.ambient.b);
	printf("difuse r[%f], g[%f], b[%f]\n", world->light.diffuse.r, world->light.diffuse.g, world->light.diffuse.b);
	printf("intensity r[%f], g[%f], b[%f]\n", world->light.intensity.r, world->light.intensity.g, world->light.intensity.b);
	printf("spehre r[%f], g[%f], b[%f]\n", world->sphs->rgb.r, world->sphs->rgb.g, world->sphs->rgb.b);*/

	set_camera(&world->cam);

	t_point	origin = create_point(0, 0, 0);
	world->cam.transform = view_transformation(world->cam.pos, origin, world->cam.n_vec);
	world->cam.invert = invert_mtx(&world->cam.transform);
	

	printf("zaloa pixel size is %f\n", pixel_size);
	printf("pixel size is %f\n", world->cam.pix_s);

	y = -1;
	while (++y < HEIGHT -1)
	{
		x = -1;
		world_y = half - (y * pixel_size);
		//printf("y es %d\n", y);
		while (++x < WIDTH - 1)
		{
			
			world_x = (-1 * half) + (x * pixel_size);
		//	position = create_point(world_x, world_y, world_z);
		//	ray = create_ray(ray_origin, normalization_vect(sub_point_point(position, ray_origin)));
			
			ray = ray_for_pixel(&world->cam, x, y);
			if ((x == 0 && y == 0) || (x == 500 && y == 500) || (x == 890 && y == 890))
			{
				printf("\nRay origin is %f, %f, %f\n", ray.origin.x, ray.origin.y, ray.origin.z);
				printf("Ray direction is ");
				print_vect(ray.direction);
				print_mtx(&world->cam.transform);
				print_mtx(&world->cam.invert);
			}
			t_color final_color = color_at(world, ray);
			mlx->img.addr[y * WIDTH + x] = convert_color_to_int(final_color);	

		}
	}
//	print_values(world);
	printf("fin\n");;
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

//1. Recoger todos los datos que nos pasan
//2. Preparar las matrices de trasnformación de  los objetos
//3. Preparar la cámara
//4. Pintar. Recorrernos toda la pantalla.
	//4. 1. Lanzar rayos.
	//4. 2. Calcular si intercepta con un objeto y cuan es el más cercano
	//4. 3. Lanzar rayos al foco de luz para calcular las sombras
	//4. 4. Pintar en la pantalla. 
void	add_walls(t_world *world)
{
	t_sphere *floor;

	add_spheres_list(world, &world->sphs);
	floor = get_last_sphere_list(&world->sphs);
	floor->transform = identity_mtx(4);
	floor->transform = set_transform_sp(*floor, translation_mtx(0, -1, 0));
//	floor->transform = set_transform_sp(*floor, y_rotatation_mtx(45));
	floor->transform = set_transform_sp(*floor, scaling_mtx(10, 0.01, 10));
	floor->transform = set_transform_sp(*floor, x_rotatation_mtx(-45));
	floor->inverse = invert_mtx(&floor->transform);
	floor->transpose = transpose_mtx(&floor->inverse);
	floor->diameter = 1;
	floor->rgb = create_color(1, 0.9, 0.5);

		
	t_sphere *right;

	add_spheres_list(world, &world->sphs);
	right = get_last_sphere_list(&world->sphs);
	right->transform = identity_mtx(4);
	right->transform = set_transform_sp(*right, translation_mtx(0, 0, 5));
	right->transform = set_transform_sp(*right, y_rotatation_mtx(45));
	right->transform = set_transform_sp(*right, x_rotatation_mtx(90));
	right->transform = set_transform_sp(*right, scaling_mtx(10, 0.01, 10));
	right->inverse = invert_mtx(&right->transform);
	right->transpose = transpose_mtx(&right->inverse);
	right->diameter = 1;
	right->rgb = create_color(1, 0.5, 0.5);

}
int	main(int argc, char **argv)
{
	int		fd;
	char		*line;
	t_world	all; 

	ft_memset(&all, 0, sizeof(t_world));
	fd = basic_error_handling(argc, argv);
	all.sphs = NULL;
	all.plns = NULL;
	all.cyls = NULL;
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		get_values(line, &all);
		free(line);
	}
	printf("\nPrepare objects transformations\n");
	prepare_object_transformations(&all);
//	add_walls(&all);
	
	{
		t_cylinder c;

		c.transform = identity_mtx(4);
		c.inverse = invert_mtx(&c.transform);
		c.transpose = transpose_mtx(&c.inverse);
		t_inter inter = intersect_ray_cyl((create_ray(create_point(1, 0, -5), create_vect(0,0,1))), c);
		t_inter inter2 = intersect_ray_cyl((create_ray(create_point(0, 0, -5), create_vect(0,0,1))), c);
		t_inter inter3 = intersect_ray_cyl((create_ray(create_point(0.5, 0, -5), create_vect(0.1,1,1))), c);
		
		printf("1. p0 [%f], p1[%f]\n", inter.point[0], inter.point[1]);
		printf("2. p0 [%f], p1[%f]\n", inter2.point[0], inter2.point[1]);
		printf("3. p0 [%f], p1[%f]\n", inter3.point[0], inter3.point[1]);

		print_vect(get_normal_cy(c, create_point(1, 0, 0)));
	}

	//print_values(&all);
	t_point point = create_point(10, -10, 10);
	bool shadow = is_shadowed(&all, point);
	printf("shadows -> %d\n", shadow);

	t_mlx	mlx;
	printf("Pintar\n");
    mlx_utils_init(&mlx);
    mlx_event(&mlx);
//    draw(&mlx);
	prueba_default(&all, &mlx);
 	 mlx_loop(mlx.mlx);
	free_structures(&all);
	close(fd);
	return 0;
}


#include	<fcntl.h>	//Open
#include	<unistd.h>	//Write
#include	"../../includes/miniRT.h"

int	is_float(char *s, int *i, int j, int nb)
{
	int	sign_dot[2];

	sign_dot[0] = 0;
	sign_dot[1] = 0;
	while (s[++j])
	{
		if (s[j] && (s[j] == '+' || s[j] == '-'))
			sign_dot[0]++;
		if (s[j] >= '0' && s[j] <= '9')
		{
			while (s[j] && s[j] >= '0' && s[j] <= '9' && ++nb)
				j++;
			if (s[j] && s[j] == '.' && j++)
				sign_dot[1]++;
			while (s[j] && s[j] >= '0' && s[j] <= '9' && ++nb)
				j++;
			break ;
		}
	}
	if (!nb || (nb == 1 && sign_dot[1]) || sign_dot[0] > 1)
		return (0);
	*i = j - 1;
	if (s[j] && s[j] == ',')
		*i = j;
	return (1);
}

int	check_format(char *s)
{
	int	i;
	int	j;
	int point;

	i = -1;
	while (s[++i])
	{
		point = 0;
		j = i;
		if (s[i] == '+' || s[i] == '-' || s[i] == '.')
		{
			if (s[i] == '.' && i > 0 && !ft_isdigit(s[i - 1]))
				return (1);
			while (s[++j] && !ft_isdigit(s[j]))
					return (1);
		}
		else if (s[i] == ',')
		{
			while (s[++j] && !ft_isdigit(s[j]) && s[j] != '+' && s[j] != '-' &&  s[j] != ' ' && s[j] != '.' )
				return (1);
			if (s[i + 1] == '\0') //Si estamos en la última línea y acaba en coma y no hay una línea vacía en el .rt hay que mirarlo. //Tambien se mira en get_data_utils/check_character En uno de los dos se puede quitar.
				return (1);
		}
	}
	return (0);
}

int	check_line_syntax(char *s)
{
	int	i;

	if (s[0] == 'A' || s[0] == 'C' || s[0] == 'L')
		i = 0;
	else if ((s[0] == 's' && s[1] && s[1] == 'p' && s[2] && s[2] == ' ')
				|| (s[0] == 'p' && s[1] && s[1] == 'l' && s[2] && s[2] == ' ')
				|| (s[0] == 'c' && s[1] && s[1] == 'y' && s[2] && s[2] == ' '))
				i = 2;
	else if (s[0] == '\n')
		i = -1;
	else
		return (0);
	if (check_format(s))
		return (1);
	while (s[++i])
	{
		if (ft_isalpha(s[i]))
			return (1);
	}
	i = 0;
	while (s[++i])
	{
		if (s[i] == '\n')
			break;
		if (ft_isdigit(s[i]) || s[i] == ',' ||  is_float(s, &i, i - 1, 0))
		{
			continue;
		}
		else if (s[i] == ' ')
			continue;
		if (s[i] == '\0') //Lo he puesto porque cuando el .rt no acaba con una línea vacía peta
			break;
	}
	return 0;
}
static void	get_values(char **line, t_world *all, int fd)
{
	int		i;
	int		out;
	char	*s;

	out = 0;
	i = -1;
	s = ft_strtrim(*line, " ");
	while(s[++i] && s[0] != '\n')
	{
		if (check_line_syntax(s))
			wrong_values_handling(&s, all, fd, 1);
		if (s[i] == 'A' && ++out)
			all->a_light = create_amblight(s, all, fd);
		if (s[i] == 'C' && ++out)
			all->cam = create_camera(s, all, fd);
		else if (s[i] == 'L' && ++out)
			all->light = create_light(s, all, fd);
		else if (s[i] == 'p' && ++out)
			create_planes(s, all, fd);
		else if (s[i] == 's' && ++out)
			create_spheres(s, all, fd);
		else if (s[i] == 'c' && ++out)
			create_cylinders(s, all, fd);
		if (out)
			break ;
	}
}

void	ray_tracing(t_world *world, t_mlx *mlx)
{
	int		x;
	int		y;
	double	world_x;
	double	world_y;
	t_point	to;
	//t_ray	ray;
/*	double	wall_size = 7;
	double	pixel_size = wall_size / HEIGHT;
	double	half = wall_size / 2;*/
	
	set_camera(&world->cam);
	to.z = world->cam.pos.z + 1;
	to.x = world->cam.pos.x + (world->cam.n_vec.x / world->cam.n_vec.z);
	to.y = world->cam.pos.y + (world->cam.n_vec.y / world->cam.n_vec.z);
	if (world->cam.n_vec.x == 0 && world->cam.n_vec.y == 1 && world->cam.n_vec.z == 0)
		world->cam.transform = view_transformation(world->cam.pos, to, create_vect(0, 0, 1));
	else
		world->cam.transform = view_transformation(world->cam.pos, to, create_vect(0, 1, 0));
	world->cam.transform = view_transformation(world->cam.pos, to, create_vect(0, 1, 0));
	world->cam.invert = invert_mtx(&world->cam.transform);
	y = -1;
	while (++y < HEIGHT -1)
	{
		x = -1;
	//	world_y = half - (y * pixel_size);
		world_y = world->cam.half_h - (y *  world->cam.pix_s);
		while (++x < WIDTH - 1)
		{
	//		world_x = (-1 * half) + (x * pixel_size);
			world_x = (-1) * world->cam.half_w - (x *  world->cam.pix_s);
		//	ray = ray_for_pixel(&world->cam, x, y);
			mlx->img.addr[y * WIDTH + x] = convert_color_to_int(color_at(world,
					ray_for_pixel(&world->cam, x, y)));	
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	t_world	all;

	ft_memset(&all, 0, sizeof(t_world));
	all = (t_world){.sphs = NULL, .plns = NULL, .cyls = NULL};
	fd = basic_error_handling(argc, argv);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		get_values(&line, &all, fd);
		free(line);
	}
	prepare_object_transformations(&all);
	t_mlx	mlx;
	 mlx_utils_init(&mlx);
	mlx_event(&mlx);
	ray_tracing(&all, &mlx);
 	mlx_loop(mlx.mlx);
	print_values(&all);
	free_structures(&all);
	close(fd);
	return 0;
}


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

	i = -1;
	while (s[++i])
	{
		j = i;
		if (s[i] == '+' || s[i] == '-' || s[i] == '.')
		{
			while (s[++j] && !ft_isdigit(s[j]))
				if (s[j] != ' ')
					return (1);
		}
		else if (s[i] == ',')
		{
			while (s[++j] && !ft_isdigit(s[j]) && s[j] != '+' && s[j] != '-')
				if (s[j] != ' ')
					return (1);
		}
	}
	return (0);
}

int	check_line_syntax(char *s)
{
	int	i;
	int	no_more_char;

	i = -1;
	no_more_char = 0;
	if (check_format(s))
		return (1);
	while (s[++i])
	{
		printf("vueltaaaaaaa     %c\n", s[i]);
		if (!ft_isalpha(s[i]) && is_float(s, &i, i - 1, 0))
			i++;
		else if (!no_more_char && (ft_strchr("ACL", s[i])
				|| (s[i] == 's' && s[++i] && s[i] == 'p' && s[++i] && s[i] == ' ')
				|| (s[i] == 'p' && s[++i] && s[i] == 'l' && s[++i] && s[i] == ' ')
				|| (s[i] == 'c' && s[++i] && s[i] == 'y' && s[++i] && s[i] == ' ')))
			no_more_char = 1;
		else
			return (1);
	}
	return 0;
}

static void	get_values(char **line, t_world *all, int fd)
{
	int	i;
	int	out;

	out = 0;
	i = -1;
	while(*line[++i] && line[i][0] != '\n')
	{
		if (check_line_syntax(*line))
			wrong_values_handling(line, all, fd);
		if (*line[i] == 'A' && ++out)
			all->a_light = create_amblight(*line);
		if (*line[i] == 'C' && ++out)
			all->cam = create_camera(*line);
		else if (*line[i] == 'L' && ++out)
			all->light = create_light(*line);
		else if (*line[i] == 'p' && ++out)
			create_planes(*line, all, fd);
		else if (*line[i] == 's' && ++out)
			create_spheres(*line, all, fd);
		else if (*line[i] == 'c' && ++out)
			create_cylinders(*line, all, fd);
		if (out)
			break ;
	}
}

void	ray_tracing(t_world *world, t_mlx *mlx)
{
	int x;
	int	y;
	double	world_x;
	double	 world_y;
	t_ray	ray;
	
	double	wall_size = 7;
	double	pixel_size = wall_size / HEIGHT;
	double	half = wall_size / 2;
	
	set_camera(&world->cam);
	t_point	to;
	to.z = world->cam.pos.z + 1;
	to.x = world->cam.pos.x + (world->cam.n_vec.x / world->cam.n_vec.z);
	to.y = world->cam.pos.y + (world->cam.n_vec.y / world->cam.n_vec.z);
	world->cam.transform = view_transformation(world->cam.pos, to, create_vect(0, 1, 0));
	world->cam.invert = invert_mtx(&world->cam.transform);

	y = -1;
	while (++y < HEIGHT -1)
	{
		x = -1;
		world_y = half - (y * pixel_size);
		while (++x < WIDTH - 1)
		{
			world_x = (-1 * half) + (x * pixel_size);
			ray = ray_for_pixel(&world->cam, x, y);
			t_color final_color = color_at(world, ray);
			mlx->img.addr[y * WIDTH + x] = convert_color_to_int(final_color);	
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
	/*
	prepare_object_transformations(&all);
	t_mlx	mlx;
  mlx_utils_init(&mlx);
  mlx_event(&mlx);
	ray_tracing(&all, &mlx);
 	mlx_loop(mlx.mlx);
	*/
	print_values(&all);
	free_structures(&all);
	close(fd);
	return 0;
}

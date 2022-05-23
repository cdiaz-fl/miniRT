
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
			while (s[++j] && !ft_isdigit(s[j]))
			{
				if (s[j] != ' ')
					return (1);
			}
		}
		else if (s[i] == ',')
		{
			while (s[++j] && !ft_isdigit(s[j]) && s[j] != '+' && s[j] != '-')
			{
				if (s[j] != ' ' || (s[j] == '.' && ++point))
				{
					if (point > 1 || s[j] != ' ')
						return (1);
				}
			}
			if (s[i + 1] == '\0') //Si estamos en la última línea y acaba en coma y no hay una línea vacía en el .rt hay que mirarlo. //Tambien se mira en get_data_utils/check_character En uno de los dos se puede quitar.
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
		printf("vueltaaaaaaa     %d\n", s[i]);
		if (s[i] == '\n')
			break;
		if ((!ft_isalpha(s[i]) && is_float(s, &i, i - 1, 0)) || s[i] == ' ') //Si nos meten muchos espacio al final de la linea
			i++;
		else if (!no_more_char && (ft_strchr("ACL", s[i])
				|| (s[i] == 's' && s[++i] && s[i] == 'p' && s[++i] && s[i] == ' ')
				|| (s[i] == 'p' && s[++i] && s[i] == 'l' && s[++i] && s[i] == ' ')
				|| (s[i] == 'c' && s[++i] && s[i] == 'y' && s[++i] && s[i] == ' ')))
			no_more_char = 1;
		else
			return (1);
		if (s[i] == '\0') //Lo he puesto porque cuando el .rt no acaba con una línea vacía peta
			break;
	}
	return 0;
}

static void	get_values(char **line, t_world *all, int fd)
{
	int	i;
	int	out;
	char *s;

	out = 0;
	i = -1;
	s = ft_strtrim(*line, " ");
	printf("len -> %zu\n", ft_strlen(s));
	printf("1. Esto igual se puede quitar lo habia hecho para quitar  los espacio por si nos meten lineas vacias solo de esapcios o tabuladores ->%s\n", s); //Pero funciona si esto.
//	s = ft_strdup(*line);
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

/*	prepare_object_transformations(&all);
	t_mlx	mlx;
  mlx_utils_init(&mlx);
  mlx_event(&mlx);
	ray_tracing(&all, &mlx);
	
 	mlx_loop(mlx.mlx);*/
	print_values(&all);
	free_structures(&all);
	close(fd);
	return 0;
}

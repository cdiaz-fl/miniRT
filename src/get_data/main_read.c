
#include	<fcntl.h>	//Open
#include	<unistd.h>	//Write
#include	"../../includes/miniRT.h"

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
		else if (!no_more_char && (ft_strchr("ACL", s[i])) /*||
			(s[i] == 's' && s[++i] && s[i] == 'p') ||
			(s[i] == 'p' && s[++i] && s[i] == 'l') ||
			(s[i] == 'c' && s[++i] && s[i] == 'y'))*/)
			no_more_char = 1;
	/*	else if (s[i] > 32)
		{
		//	printf("muere -> %c\n", s[i]);
			return 1;
		}*/

	}
	return 0;
}

void	get_values(char *line, t_objects *all)
{
	int	i;

	i = -1;
	while(line[++i])
	{
	//	if (check_line_syntax(line))
	//		wrong_values_handling(line, all);
		if (line[i] == 'A')
			create_amblight(line, all);
		if (line[i] == 'C')
			create_camera(line, i, all);
		else if (line[i] == 'L')
			create_light(line, all);
//		else if (line[i] == 'p')
//			all->plns[all->plns_nb] = create_planes(line, i, all);
		else if (line[i] == 's')
			create_spheres(line, all);
/*		else if (line[i] == 'c')
			all->cyls[all->cyls_nb] = create_cylinder(line, i, all);*/
	//	else if (line[i] > 32) //Es char imprimible
	//		wrong_values_handling(line, all);
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

void	print_values(t_objects	*all)
{
	t_sphere	*tmp;
	t_sphere	**s_head;

	printf("\n\n--------------------  Camera  ---------------------\n");
	printf("|                                                 |\n");
	printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", all->cam->pos.x, all->cam->pos.y, all->cam->pos.z);
	printf("|    nx = %6.2f    ny = %6.2f    nz = %6.2f    |\n", all->cam->n_vec.x, all->cam->n_vec.y, all->cam->n_vec.z);
	printf("|    FOV = %6d                                 |\n", all->cam->FOV);
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");

	
	printf("\n\n--------------------  ALight  ---------------------\n");
	printf("|                                                 |\n");
	printf("|     rate = %6.2f                               |\n", all->a_light->rate);
	printf("|     R = %6d   G = %6d    B = %6d       |\n", all->a_light->r, all->a_light->g, all->a_light->b);
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");

	printf("\n\n--------------------   Light  ---------------------\n");
	printf("|                                                 |\n");
	printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", all->light->pos.x, all->light->pos.y, all->light->pos.z);
	printf("|     glow = %6.2f                               |\n", all->light->glow);
	printf("|     R = %6d   G = %6d    B = %6d       |\n", all->light->r, all->light->g, all->light->b);
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");

	printf("\n\n--------------------  Sphers  ---------------------\n");
	printf("|                                                 |\n");
	s_head = &all->sphs;
	tmp = *s_head;
	int	i;
	i = 0;
	while (tmp->next != NULL && ++i)
	{
		printf("|     Number = %6d                                   |\n", i);
		printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", tmp->pos.x, tmp->pos.y, tmp->pos.z);
		printf("|     diam = %6.2f                               |\n", tmp->diameter);
		printf("|     R = %6d   G = %6d    B = %6d       |\n", tmp->r, tmp->g, tmp->b);
	}
	printf("|                                                 |\n");
	printf("|     Number = %d                                 |\n", i);
	printf("|     x = %6.2f     y = %6.2f     z = %6.2f    |\n", tmp->pos.x, tmp->pos.y, tmp->pos.z);
	printf("|     diam = %6.2f                               |\n", tmp->diameter);
	printf("|     R = %6d   G = %6d    B = %6d       |\n", tmp->r, tmp->g, tmp->b);
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");

	printf("\n\n--------------------  Planes  ---------------------\n");
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");

	printf("\n\n--------------------  Cylinds ---------------------\n");
	printf("|                                                 |\n");
	printf("---------------------------------------------------\n");
}

int	main(int argc, char **argv)
{
	int		fd;
	char		*line;
	t_objects	all; //Hay que inicializar all

	fd = basic_error_handling(argc, argv);
	all.sphs = NULL;	//ft_initialize
	//Falta incluir librería gnl
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		get_values(line, &all);
		free(line);
	}
	print_values(&all);
	close(fd);
	return 0;
}

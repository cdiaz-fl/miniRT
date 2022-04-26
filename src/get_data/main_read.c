
#include	<fcntl.h>	//Open
#include	<unistd.h>	//Write
#include	"../../includes/miniRT.h"

void	fill_amblight_data(t_amb_light *amb, int variable, float nbr)
{
	if (variable == 0)
		amb->rate = nbr;
	else if (variable == 1)
		amb->r = (int)nbr;
	else if (variable == 2)
		amb->g = (int)nbr;
	else if (variable == 3)
		amb->b = (int)nbr;
}

int	create_amblight(char *line, t_objects *all)
{
	int i;
	int variable;

	i = 0;
	variable = 0; 
	while (line[++i])
	{
		if (ft_isdigit(line[i]) || line[i] == '-')
		{
			fill_amblight_data(&all->a_light, variable, ft_atof(&line[i], 10));
			variable++;
			while (ft_isdigit(line[i]) || line[i] == '.')
				i++;

		}
		else if (line[i] == ',' || line[i] == 32)
			continue;
//		else
 //			write(2, "Wrong parameters ❌\n", 21);

	}
	return (1);
}

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
/*		else if (line[i] == 'C')
			all->cam = create_camera(line, i, all);
		else if (line[i] == 'L')
			all->light = create_light(line, i, all);
		else if (line[i] == 'p')
			all->plns[all->plns_nb] = create_planes(line, i, all);
		else if (line[i] == 's')
			all->sphs[all->sphs_nb] = create_sphere(line, i, all);
		else if (line[i] == 'c')
			all->cyls[all->cyls_nb] = create_cylinder(line, i, all);*/
	//	else if (line[i] > 32) //Es char imprimible
	//		wrong_values_handling(line, all);
	}
	printf("rate -> %f\n", all->a_light.rate);
	printf("r -> %d\n", all->a_light.r);
	printf("g -> %d\n", all->a_light.g);
	printf("b -> %d\n", all->a_light.b);
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


int	main(int argc, char **argv)
{
	int		fd;
	char		*line;
	t_objects	all; //Hay que inicializar all

	fd = basic_error_handling(argc, argv);
	//Falta incluir librería gnl
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		get_values(line, &all);
		free(line);
	}
	close(fd);
	return 0;
}

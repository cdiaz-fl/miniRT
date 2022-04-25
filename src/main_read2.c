/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_read2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:52:42 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/25 11:59:46 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include	<fcntl.h>	//Open
#include	<unistd.h>	//Write
#include	"../includes/miniRT_temp.h"

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
			fill_amblight_data(&all->a_light, variable, ft_atof(&line[i]));
			variable++;
			while (ft_isdigit(line[i]) || line[i] == '.')
				i++;
			if (line[i] != '\n' && line[i] != ',' && line[i] != 32 && line[i] != '.')
			{
 				write(2, "Wrong parameters ❌\n", 21);
				exit(0);
			}

		}
		else if (line[i] == ',' || line[i] == 32)
			continue;
//		else
 //			write(2, "Wrong parameters ❌\n", 21);

	}
	printf("rate -> %f\n", all->a_light.rate);
	printf("r -> %d\n", all->a_light.r);
	printf("g -> %d\n", all->a_light.g);
	printf("b -> %d\n", all->a_light.b);
	return (1);
}


int	get_val(char *line, t_objects *all)
{
	int	i;


	i = -1;
	printf("AQUI\n");
	while (line[++i])
	{
		//Falta incluir Libft
		//Qué te parece este enfoque?
		if ((line[i] == 'A' && create_amblight(&line[i],  all)))
	/*		|| (line[i] == 'C' && create_camera(line, i, all))
			|| (line[i] == 'L' && create_light(line, i, all))
			|| (line[i] == 'p' && create_planes(line, i, all))
			|| (line[i] == 's' && create_sphere(line, i, all))
			|| (line[i] == 'c' && create_cylinder(line, i, all)))*/
			 return 0;
		else
			return 1;
//		else if (line[i] > 32 && line[i] < 128) //Es char imprimible
//			return	1;
	}
	return 0;
}

int	main(int argc, char **argv)
{
	int		fd;
	char		*line;
	t_objects	all; //Hay que inicializar all

	if (argc != 2 && write(2, "\e[1;31mError\n", 13))
	{
 		write(2, "Wrong parameters ❌\n", 21);
		return 0;
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1 && write(2, "\e[1;31mError\n", 13))
	{
 		write(2, "Invalid file ❌\n", 17);
		return 0;
	}

	//Falata incluir librería gnl
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (get_val(line, &all) && write(2, "\e[1;31mError\n", 13))
		{
 			write(2, "Wrong values ❌\n", 17);
			//free_objects();
			close(fd);
		}		
		free(line);
	}
	close(fd);
	return 0;
}

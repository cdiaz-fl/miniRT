
#include	<fcntl.h>	//Open
#include	<unistd.h>	//Write
#include	"objects.h"

int	get_val(char *line, t_objects *all)
{
	int	i;


	i = -1;
	while(line[++i])
	{
		//Falta incluir Libft
		//Qué te parece este enfoque?
		if ((line[i] == 'A' && create_amblight(line, i, all))
			|| (line[i] == 'C' && create_camera(line, i, all))
			|| (line[i] == 'L' && create_light(line, i, all))
			|| (line[i] == 'p' && create_planes(line, i, all))
			|| (line[i] == 's' && create_sphere(line, i, all))
			|| (line[i] == 'c' && create_cylinder(line, i, all)))
			 return 1;
		else if (line[i] > 32 && line[i] < 128) //Es char imprimible
			return	1;
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
		if (get_val(line, &all) && write(2, "\e[1;31mError\n", 13));
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

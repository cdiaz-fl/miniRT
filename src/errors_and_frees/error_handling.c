/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiaz-fl <cdiaz-fl@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 09:37:41 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/17 09:11:54 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/miniRT.h"
#include	<fcntl.h>	//Open

void	wrong_values_handling(char **line, t_world *all, int fd, int error)
{
//	(void)all;
	write(2, "\e[1;31mError\n", 13);
	if (error == 1)
		write(2, "Wrong values: Unexpected char ❌\n", 33);
	else if (error ==  2)
		write(2, "Wrong values: Sphere problem ❌\n", 32);
	else if (error ==  3)
		write(2, "Wrong values: Plane problem ❌\n", 31);
	else if (error == 4) 
		write(2, "Wrong values: Cylinder problem ❌\n", 34);
	else 
		write(2, "Wrong values: Camera/Light/Ambient problem ❌\n", 46);
	free_structures(all);
	(void)line;
	//free(*line);
	close(fd);
	exit(1);
}

int	basic_error_handling(int argc, char **argv)
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
	return (fd);
}

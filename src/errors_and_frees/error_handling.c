/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 09:37:41 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/13 09:37:41 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/miniRT.h"
#include	<fcntl.h>	//Open

void	wrong_values_handling(char *line, t_world *all)
{
	(void)all;
	write(2, "\e[1;31mError\n", 1);
	write(2, "Wrong values ❌\n", 20);
	printf("FIN\n");
	//free_objects(); Hay que liberar sphs, plns, cyls
	free(line);
	//close(fd);
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

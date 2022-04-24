#include	"errors.h"

void	wrong_values_handling(char *line, t_objects *all)
{
	write(2, "\e[1;31mError\n", 13);
 	write(2, "Wrong values ❌\n", 17);
	//free_objects(); Hay que liberar sphs, plns, cyls
	free(line);
	close(fd);
	exit(1);
}

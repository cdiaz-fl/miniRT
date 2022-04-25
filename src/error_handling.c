#include	"../includes/miniRT_temp.h"

void	wrong_values_handling(char *line, t_objects *all)
{
	write(2, "\e[1;31mError\n", 1);
 	write(2, "Wrong values ❌\n", 20);
	printf("FINA\n");
	//free_objects(); Hay que liberar sphs, plns, cyls
	free(line);
	//close(fd);
	exit(1);
}

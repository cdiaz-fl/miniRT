#include	"../../includes/miniRT.h"

void	wrong_values_handling(char *line, t_world *all)
{
	(void)all;
	write(2, "\e[1;31mError\n", 1);
 	write(2, "Wrong values ❌\n", 20);
	printf("FINA\n");
	//free_objects(); Hay que liberar sphs, plns, cyls
	free(line);
	//close(fd);
	exit(1);
}



void	free_structures(t_world  *w)
{
	t_sphere *temp_s;
	t_plane *temp_p;
	t_cylinder *temp_c;
	
	temp_s = w->sphs;
	temp_p = w->plns;
	temp_c = w->cyls;
	while (w->sphs)
	{
		free_mtx(&w->sphs->transform);
		free_mtx(&w->sphs->inverse);
		free_mtx(&w->sphs->transpose);
		w->sphs = w->sphs->next;
		free(temp_s);
		temp_s = w->sphs;
	}
/*	while (w->plns->next != NULL)
	{
//		free_mtx(&w->plns->transform);
//		free_mtx(&w->plns->inverse);
//		free_mtx(&w->plns->transpose);
		w->plns = w->plns->next;
	//	free(temp_p);
		temp_p = w->plns;
	}
	while (w->cyls->next != NULL)
	{
//		free_mtx(&w->cyls->transform);
//		free_mtx(&w->cyls->inverse);
//		free_mtx(&w->cyls->transpose);
		w->cyls = w->cyls->next;
	//	free(temp_c);
		temp_c = w->cyls;
	}
*/

}


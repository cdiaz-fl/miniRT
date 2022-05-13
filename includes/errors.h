
#ifndef ERRORS_H
# define ERRORS_H

void	wrong_values_handling(char *line, t_world *all);
int	    basic_error_handling(int argc, char **argv);

void	free_structures(t_world  *w);
void	free_inter_lst(t_inter *head);
#endif

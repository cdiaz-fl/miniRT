
#ifndef ERRORS_H
# define ERRORS_H

void	wrong_values_handling(char **line, t_world *all, int fd, int error);
int	    basic_error_handling(int argc, char **argv);
void    status_error(int err, char *str);
void	free_structures(t_world  *w);
void	free_inter_lst(t_inter *head);
void	free_2d_array(char **s);
#endif

#include "../../includes/miniRT.h"

void	create_spheres_list(t_world *all)
{
	all->sphs = (t_sphere *)malloc(sizeof(t_sphere));
	if (!all->sphs)
		perror("Error: ");  //liberar->y ->xit
	all->sphs->next = NULL;
	all->sphs->transform = identity_mtx(4);
	all->sphs->inverse = identity_mtx(4);
	all->sphs->transpose = identity_mtx(4);
}

void	add_spheres_list(t_sphere **head)
{
	t_sphere *temp;
	t_sphere *new;



	new = (t_sphere *)malloc(sizeof(t_sphere));
	if (!new)
		perror("Error: ");  //liberar->y ->xit
	temp = *head;
	while (temp->next != NULL)
	{
	//	printf("add\n");
		temp = temp->next;
	}
	temp->next = new;
	new->next = NULL;
}

t_sphere	*get_last_sphere_list(t_sphere **head)
{
	t_sphere *temp;

	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	return temp;
}

void	create_spheres(char *s, t_world *all, int fd)
{
	t_sphere	*tmp;
	char		**val;
	double		*data[7];

	if (all->sphs != NULL)
		add_spheres_list(&all->sphs);
	if (!all->sphs)
		create_spheres_list(all);
	tmp = get_last_sphere_list(&all->sphs);

	val = ft_split(s, ' ');
	data[0] = &tmp->pos.x;
	data[1] = &tmp->pos.y;
	data[2] = &tmp->pos.z;
	data[3] = &tmp->diameter;
	data[4] = &tmp->rgb.r;
	data[5] = &tmp->rgb.g;
	data[6] = &tmp->rgb.b;

	tmp->transform = identity_mtx(4);
	tmp->inverse = identity_mtx(4);
	tmp->transpose = identity_mtx(4);
	if (ft_get_2d_size(val) < 4 || extract_values(val, data, "sp"))
	{
		free_2d_array(val);
		wrong_values_handling(&s, all, fd);
	}
	tmp->next = NULL;
	free(val);
}

/*
	s += 2;
	while (s && *s == ' ')
		s++;
	get_pos(tmp, &s, 's', s);
	tmp->diameter = ft_atof(s, 10);
	while (s && *s == ' ')
		s++;
	s = ft_strchr(s, ' ');
	get_rgb(tmp, s, 's');
*/
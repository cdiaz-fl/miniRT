#include "../../includes/miniRT.h"

static void	create_cylinders_list(t_world *all)
{
	all->cyls = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!all->cyls)
		perror("Error: ");  //liberar->y ->xit
	all->cyls->next = NULL;
}

void	add_cylinders_list(t_cylinder **head)
{
	t_cylinder *temp;
	t_cylinder *new;

 
	new = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!new)
		perror("Error: ");  //liberar->y ->xit
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
}

t_cylinder	*get_last_cylinder_list(t_cylinder **head)
{
	t_cylinder *temp;

	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	return temp;
}

void	create_cylinders(char *s, t_world *all)
{
	t_cylinder	*tmp;

	if (all->cyls != NULL)
		add_cylinders_list( &all->cyls);
	if (!all->cyls)
		create_cylinders_list(all);
	tmp = get_last_cylinder_list(&all->cyls);
	s += 2;
	while (s && *s == ' ')
		s++;
	tmp->pos.x = ft_atof(s, 10);
	s = ft_strchr(s, ',');
	tmp->pos.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	tmp->pos.z = ft_atof(++s, 10);


	s = ft_strchr(s, ' ');
	tmp->n_vec.x = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	tmp->n_vec.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	tmp->n_vec.z = ft_atof(++s, 10);
	s = ft_strchr(s, ' ');

	tmp->diameter = ft_atof(s, 10);
	while (s && *s == ' ')
		s++;
	s = ft_strchr(s, ' ');

	tmp->height = ft_atof(s, 10);
	while (s && *s == ' ')
		s++;
	s = ft_strchr(s, ' ');

	tmp->rgb.r = ft_atoi(++s) / 255;
	while (s && *s != ',')
		s++;
	tmp->rgb.g = ft_atoi(++s) / 255;
	while (s && *s != ',')
		s++;
	tmp->rgb.b = ft_atoi(++s) / 255;
	tmp->next = NULL;
}

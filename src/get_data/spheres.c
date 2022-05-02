#include "../../includes/miniRT.h"

void	create_spheres_list(t_world *all)
{
	all->sphs = (t_sphere *)malloc(sizeof(t_sphere));
	if (!all->sphs)
		perror("Error: ");  //liberar->y ->xit
	all->sphs->next = NULL;
}

void	add_spheres_list(t_world *all, t_sphere **head)
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

void	create_spheres(char *s, t_world *all)
{
	t_sphere	*tmp;

	if (all->sphs != NULL)
		add_spheres_list(all, &all->sphs);
	if (!all->sphs)
		create_spheres_list(all);
	tmp = get_last_sphere_list(&all->sphs);
	s += 2;
	while (s && *s == ' ')
		s++;
	tmp->pos.x = ft_atof(s, 10);
	s = ft_strchr(s, ',');
	tmp->pos.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	tmp->pos.z = ft_atof(++s, 10);

	s = ft_strchr(s, ' ');
	tmp->diameter = ft_atof(s, 10);

	while (s && *s == ' ')
		s++;
	s = ft_strchr(s, ' ');

	tmp->rgb.r = (double)ft_atoi(++s) / 255;
	while (s && *s != ',')
		s++;
	tmp->rgb.g = (double)ft_atoi(++s) / 255;
	while (s && *s != ',')
		s++;
	tmp->rgb.b = (double)ft_atoi(++s) / 255;
	tmp->next = NULL;
}

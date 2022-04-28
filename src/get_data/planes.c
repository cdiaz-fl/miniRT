#include "../../includes/miniRT.h"

static void	create_planes_list(t_objects *all)
{
	all->plns = (t_plane *)malloc(sizeof(t_plane));
	if (!all->plns)
		perror("Error: ");  //liberar->y ->xit
	all->plns->next = NULL;
}

static void	add_planes_list(t_objects *all, t_plane **head)
{
	t_plane *temp;
	t_plane *new;



	new = (t_plane *)malloc(sizeof(t_plane));
	if (!new)
		perror("Error: ");  //liberar->y ->xit
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
}

t_plane	*get_last_plane_list(t_plane **head)
{
	t_plane *temp;

	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	return temp;
}

void	create_planes(char *s, t_objects *all)
{
	t_plane	*tmp;

	if (all->plns != NULL)
		add_planes_list(all, &all->plns);
	if (!all->plns)
		create_planes_list(all);
	tmp = get_last_plane_list(&all->plns);
	s += 2;
	while (s && *s == ' ')
		s++;
	tmp->pos.x = ft_atof(s, 10);
	s = ft_strchr(s, ',');
	tmp->pos.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	tmp->pos.z = ft_atof(++s, 10);
	
	printf("line es %s \n", s);
	s = ft_strchr(s, ' ');
	tmp->n_vec.x = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	tmp->n_vec.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	tmp->n_vec.z = ft_atof(++s, 10);
	printf("line2 es %s \n", s);
	s = ft_strchr(s, ' ');

	tmp->rgb.r = ft_atoi(++s);
	while (s && *s != ',')
		s++;
	tmp->rgb.g = ft_atoi(++s);
	while (s && *s != ',')
		s++;
	tmp->rgb.b = ft_atoi(++s);
	tmp->next = NULL;
}

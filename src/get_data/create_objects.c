
#include "../../includes/miniRT.h"


void	create_camera(char *s, int i, t_objects *all)
{
	t_camera	*new;

	//if (all->cam->pos->x)	Comprobar que solo h->y una cámara
	//	wrong_values_handling(s, all);
	new = (t_camera *)malloc(sizeof(t_camera));
	if (!new)
		perror("Error: ");  //liberar->y ->xit

	new->pos.x = ft_atof(&s[++i], 10);
	s = ft_strchr(s, ',');
	new->pos.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	new->pos.z = ft_atof(++s, 10);
	s = ft_strchr(s, ' ');

	new->n_vec.x = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	new->n_vec.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	new->n_vec.z = ft_atof(++s, 10);
	s = ft_strchr(s, ' ');

	new->FOV = ft_atoi(++s);

	all->cam = new;
	if (!all->cam)
		wrong_values_handling(s, all);
}

void	create_amblight(char *s, t_objects *all)
{
	//if (all->cam->pos->x)	Comprobar que solo h->y una cámara
	//	wrong_values_handling(s, all);
	all->a_light = (t_amb_light *)malloc(sizeof(t_amb_light));
	if (!all->a_light)
		perror("Error: ");  //liberar->y ->xit

	s++;
	while (s && *s == ' ')
		s++;
	all->a_light->rate = ft_atof(s, 10);
	while (s && *s != ' ')
		s++;
	all->a_light->r = ft_atoi(++s);
	while (s && *s != ',')
		s++;
	all->a_light->g = ft_atoi(++s);
	while (s && *s != ',')
		s++;
	all->a_light->b = ft_atoi(++s);
}

void	create_light(char *s, t_objects *all)
{
	//if (all->cam->pos->x)	Comprobar que solo h->y una cámara
	//	wrong_values_handling(s, all);
	all->light = (t_light *)malloc(sizeof(t_light));
	if (!all->light)
		perror("Error: ");  //liberar->y ->xit

	s++;
	while (s && *s == ' ')
		s++;
	all->light->pos.x = ft_atof(s, 10);
	s = ft_strchr(s, ',');
	all->light->pos.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	all->light->pos.z = ft_atof(++s, 10);

	s = ft_strchr(s, ' ');
	all->light->glow = ft_atof(s, 10);

	while (s && *s == ' ')
		s++;
	s = ft_strchr(s, ' ');

	all->light->r = ft_atoi(++s);
	while (s && *s != ',')
		s++;
	all->light->g = ft_atoi(++s);
	while (s && *s != ',')
		s++;
	all->light->b = ft_atoi(++s);
}

/*
void	create_planes(char *s, t_objects *all)
{
	//if (all->cam->pos->x)	Comprobar que solo h->y una cámara
	//	wrong_values_handling(s, all);
	all->light = (t_light *)malloc(sizeof(t_light));
	if (!all->light)
		perror("Error: ");  //liberar->y ->xit

	s++;
	while (s && *s == ' ')
		s++;
	all->light->pos.x = ft_atof(s, 10);
	s = ft_strchr(s, ',');
	all->light->pos.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	all->light->pos.z = ft_atof(++s, 10);

	s = ft_strchr(s, ' ');
	all->light->glow = ft_atof(s, 10);

	while (s && *s == ' ')
		s++;
	s = ft_strchr(s, ' ');

	all->light->r = ft_atoi(++s);
	while (s && *s != ',')
		s++;
	all->light->g = ft_atoi(++s);
	while (s && *s != ',')
		s++;
	all->light->b = ft_atoi(++s);
}*/

void	create_spheres_list(t_objects *all)
{
	all->sphs = (t_sphere *)malloc(sizeof(t_sphere));
	if (!all->sphs)
		perror("Error: ");  //liberar->y ->xit
	all->sphs->next = NULL;
}

void	add_spheres_list(t_objects *all, t_sphere **head)
{
	t_sphere *temp;
	t_sphere *new;



	new = (t_sphere *)malloc(sizeof(t_sphere));
	if (!new)
		perror("Error: ");  //liberar->y ->xit
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
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

void	create_spheres(char *s, t_objects *all)
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

	tmp->r = ft_atoi(++s);
	while (s && *s != ',')
		s++;
	tmp->g = ft_atoi(++s);
	while (s && *s != ',')
		s++;
	tmp->b = ft_atoi(++s);
}

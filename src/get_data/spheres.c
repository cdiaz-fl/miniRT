#include "../../includes/miniRT.h"

void	add_spheres_list(t_sphere **head)
{
	t_sphere *temp;
	t_sphere *new;

	new = (t_sphere *)malloc(sizeof(t_sphere));
	if (!new)
		perror("Error: ");  //liberar->y ->xit
	new->next = NULL;
	new->transform = identity_mtx(4);
	new->inverse = identity_mtx(4);
	new->transpose = identity_mtx(4); 
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
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

void	create_spheres(char *s, t_world *all, int fd)
{
	t_sphere	*tmp;
	char 		**dd;
	char		**s_temp;

	add_spheres_list(&all->sphs);
	tmp = get_last_sphere_list(&all->sphs);
	if (check_character(s, ',') != 5 || check_character(s,' ') < 4)
		wrong_values_handling(&s, all, fd, 2);
	dd = ft_split(s, ',');
	tmp->pos.x = ft_atof(&dd[0][2], 10);
	tmp->pos.y = ft_atof(dd[1], 10);
	tmp->pos.z = ft_atof(dd[2], 10);
	s_temp = ft_split(dd[2], ' ');
	tmp->diameter = ft_atof(s_temp[1], 10);
	tmp->rgb.r = ft_atof(s_temp[2], 10) / 255;	
	free_2d_array(s_temp);
	tmp->rgb.g = ft_atof(dd[3], 10) / 255;	
	tmp->rgb.b = ft_atof(dd[4], 10) / 255;
	if (check_ranges((void *)tmp, 's'))
		wrong_values_handling(&s, all, fd, 3);
	free_2d_array(dd);
	/*
	char		**val;
	double		*data[7];
	
	val = ft_split(s, ' ');
	data[0] = &tmp->pos.x;
	data[1] = &tmp->pos.y;
	data[2] = &tmp->pos.z;
	data[3] = &tmp->diameter;
	data[4] = &tmp->rgb.r;
	data[5] = &tmp->rgb.g;
	data[6] = &tmp->rgb.b;
	if (ft_get_2d_size(val) < 4 || extract_values(val, data, "sp") || check_ranges((void *)tmp, 's'))
	{
		free_2d_array(val);
		wrong_values_handling(&s, all, fd, 2);
	}
	//A ver si lo pueedo poner dentro de check_ranges.Luego lo miro
	tmp->rgb.r /= 255;
	tmp->rgb.g /= 255;
	tmp->rgb.b /= 255;
	tmp->next = NULL;
	free_2d_array(val);*/
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
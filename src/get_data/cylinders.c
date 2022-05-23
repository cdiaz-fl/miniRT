#include "../../includes/miniRT.h"

t_cylinder	*get_last_cylinder_list(t_cylinder **head)
{
	t_cylinder *temp;

	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	return temp;
}

void	add_cylinders_list(t_cylinder **head)
{
	t_cylinder *temp;
	t_cylinder *new;

 
	new = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!new)
		perror("Error: "); 
	new->next = NULL;
	new->transform = identity_mtx(4);
	new->inverse = identity_mtx(4);
	new->transpose = identity_mtx(4); //liberar->y ->xit
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

void	create_cylinders(char *s, t_world *all, int fd)
{
	t_cylinder	*tmp;
	char 		**dd;
	char		**s_temp;

	add_cylinders_list(&all->cyls);	//Lo que antes se hacia en 2 funciones lo he unido todo en esta.
	tmp = get_last_cylinder_list(&all->cyls);
	if (check_character(s, ',') != 7 || check_character(s, ' ') < 6)
		wrong_values_handling(&s, all, fd, 4);
	dd = ft_split(s, ',');
	tmp->pos.x = ft_atof(&dd[0][2], 10);
	tmp->pos.y = ft_atof(dd[1], 10);
	tmp->pos.z = ft_atof(dd[2], 10);
	s_temp = ft_split(dd[2], ' ');
	tmp->n_vec.x = ft_atof(s_temp[1], 10);
	free_2d_array(s_temp);
	tmp->n_vec.y = ft_atof(dd[3], 10);
	tmp->n_vec.z = ft_atof(dd[4], 10);	
	s_temp = ft_split(dd[4], ' ');
	tmp->diameter = ft_atof(s_temp[1], 10);
	tmp->height = ft_atof(s_temp[2], 10);
	tmp->rgb.r = ft_atof(s_temp[3], 10) / 255;	
	free_2d_array(s_temp);
	tmp->rgb.g = ft_atof(dd[5], 10) / 255;	
	tmp->rgb.b = ft_atof(dd[6], 10) / 255;
	if (check_ranges((void *)tmp, 'c'))
		wrong_values_handling(&s, all, fd, 3);
	free_2d_array(dd);
	/*char		**val;
	double		*data[11];
	val = ft_split(s, ' ');
	data[0] = &tmp->pos.x;
	data[1] = &tmp->pos.y;
	data[2] = &tmp->pos.z;
	data[3] = &tmp->n_vec.x;
	data[4] = &tmp->n_vec.y;
	data[5] = &tmp->n_vec.z;
	data[6] = &tmp->diameter;
	data[7] = &tmp->height;
	data[8] = &tmp->rgb.r;
	data[9] = &tmp->rgb.g;
	data[10] = &tmp->rgb.b;
	if (ft_get_2d_size(val) < 6 || extract_values(val, data, "cy") ||  check_ranges((void *)tmp, 'c'))
	{
		free_2d_array(val);	//Podemos no liberar esto y nos ahorramos 3 lineas
		wrong_values_handling(&s, all, fd, 4);
	}
	free_2d_array(val);
	tmp->next = NULL;
	*/
}

/*
	s += 2;
	while (s && (*s == ' ' || *s == '	'))
		s++;
	get_pos(tmp, &s, 'c', s);
	get_n_vec(tmp, &s, 'c', s);
	tmp->diameter = ft_atof(s, 10);
	while (s && (*s == ' ' || *s != '	'))
		s++;
	while (s && *s != ' ' && *s != '	')
		s++;
	printf("antes rgb = [%s]\n", s);
	tmp->height = ft_atof(s, 10);
	while (s && *s != ' ' && *s != '	')
		s++;
	get_rgb((void *)tmp, s, 'c');
*/
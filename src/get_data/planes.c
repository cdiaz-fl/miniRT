#include "../../includes/miniRT.h"


static void	add_planes_list(t_plane **head)
{
	t_plane *temp;
	t_plane *new;

	new = (t_plane *)malloc(sizeof(t_plane));
	if (!new)
		perror("Error: ");
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

t_plane	*get_last_plane_list(t_plane **head)
{
	t_plane *temp;

	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	return temp;
}

void	create_planes(char *s, t_world *all, int fd)
{
	t_plane	*tmp;
	char **dd;
	char **s_temp;

	add_planes_list(&all->plns);
	tmp = get_last_plane_list(&all->plns);
	if (check_character(s, ',') != 7 || check_character(s, ' ') < 3)
		wrong_values_handling(&s, all, fd, 3);
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
	tmp->rgb.r = ft_atof(s_temp[1], 10) / 255;	
	free_2d_array(s_temp);
	tmp->rgb.g = ft_atof(dd[5], 10) / 255;	
	tmp->rgb.b = ft_atof(dd[6], 10) / 255;
	if (check_ranges((void *)tmp, 'p'))
		wrong_values_handling(&s, all, fd, 3);
	free_2d_array(dd);
/*	char	**val;
	double	*data[9];
	
	val = ft_split(s, ' ');
	data[0] = &tmp->pos.x;
	data[1] = &tmp->pos.y;
	data[2] = &tmp->pos.z;
	data[3] = &tmp->n_vec.x;
	data[4] = &tmp->n_vec.y;
	data[5] = &tmp->n_vec.z;
	data[6] = &tmp->rgb.r;
	data[7] = &tmp->rgb.g;
	data[8] = &tmp->rgb.b;
	if (ft_get_2d_size(val) < 3 || extract_values(val, data, "pl") || check_ranges((void *)tmp, 'p'))
	{
		free_2d_array(val);
		wrong_values_handling(&s, all, fd, 3);
	}
	free(val);
	tmp->rgb.r /= 255;
	tmp->rgb.g /= 255;
	tmp->rgb.b /= 255;
	//A ver si lo pueedo poner dentro de check_ranges.Luego lo miro
	tmp->next = NULL;*/
}

/*
	s += 2;
	while (s && (*s == ' ' || *s == '	'))
		s++;
	printf("antes pos = [%s]\n", s);
	get_pos(tmp, &s, 'p', s);
	printf("después pos = [%s]\n", s);
	printf("antes vec = [%s]\n", s);
	get_n_vec(tmp, &s, 'p', s);
	while (s && *s != ' ' && *s != '	')
		s++;
	printf("después vec = [%s]\n", s);
	get_rgb((void *)tmp, s, 'p');
*/
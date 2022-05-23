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
	char	**val;
	double	*data[9];

	add_planes_list(&all->plns);
	tmp = get_last_plane_list(&all->plns);
	if (check_character(s, ',') != 7)
		wrong_values_handling(&s, all, fd, 3);
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
	//A ver si lo pueedo poner dentro de check_ranges.Luego lo miro
	tmp->rgb.r /= 255;
	tmp->rgb.g /= 255;
	tmp->rgb.b /= 255;
	tmp->next = NULL;
	free(val);
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
#include "../../includes/miniRT.h"

static void	create_cylinders_list(t_world *all)
{
	all->cyls = (t_cylinder *)malloc(sizeof(t_cylinder));
	if (!all->cyls)
		perror("Error: ");  //liberar->y ->xit
	all->cyls->next = NULL;
	all->cyls->transform = identity_mtx(4);
	all->cyls->inverse = identity_mtx(4);
	all->cyls->transpose = identity_mtx(4);
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

size_t	ft_get_2d_size(char **s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
	{
		printf("dim %zu = [%s]\n", i, s[i]);
		i++;
	}
	return (i);
}

int	extract_values(char **val, double **data, char *type)
{
	int	i;
	int	j;
	int	k;

	k = -1;
	i = -1;
	while (val[++i])
	{
		j = -1;
		while (val[i][++j])
		{
			if (val[i][j] == 47 || val[i][j] < 43 || (val[i][j] > '9'
				&& val[i][j] != type[0] && val[i][j] != type[1]))
			{
				printf("salgoooo\n");
				return (1);
			}
			if (val[i][j] <= '9')
			{
				if ((type[0] == 'p' && k == 8) || (type[0] == 'c' && k == 10) || (type[0] == 's' && k == 6))
				{
					printf("salgoooo\n");
					return (1);
				}
				printf("k es %d\n", k);
				*data[++k] = ft_atof(val[i] + j, 10);
				printf("value = %f\n", *data[k]);
				while (val[i][++j] && val[i][j] != ',' && val[i][j] != '\n')
				{
					printf("s = %c\n", val[i][j]);
					if (val[i][j] && (val[i][j] > '9' || val[i][j] < 43 || val[i][j] == 47))
					{
						printf("pepepe\n");
						return (1); 
					}
				}
				if (!val[i][j])
					j--;
				if (val[i][j] && val[i][j + 1] && (val[i][j + 1] == ',' || val[i][j + 1] == '.'))
				{
					printf("paco\n");
					return (1);
				}
			}
		}
	}
	return (0);
}

void	free_2d_array(char **s)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
		free(s[i]);
	free(s);
}

void	create_cylinders(char *s, t_world *all, int fd)
{
	t_cylinder	*tmp;
	char		**val;
	double		*data[11];

	if (all->cyls != NULL)
		add_cylinders_list(&all->cyls);
	if (!all->cyls)
		create_cylinders_list(all);
	tmp = get_last_cylinder_list(&all->cyls);
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
	tmp->transform = identity_mtx(4);
	tmp->inverse = identity_mtx(4);
	tmp->transpose = identity_mtx(4);
	if (ft_get_2d_size(val) < 6 || extract_values(val, data, "cy"))
	{
		free_2d_array(val);
		wrong_values_handling(&s, all, fd);
	}
	tmp->next = NULL;
	free(val);
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
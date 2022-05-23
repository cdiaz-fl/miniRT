/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 10:08:30 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/23 10:08:31 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	check_character(char *s, char c)
{
	char **temp;
    int nbr_character;

	temp = ft_split(s, c);
    nbr_character = ft_get_2d_size(temp);
	//printf("nbr commaaàs -> %zu\n", ft_get_2d_size(temp));
  //  printf("Ultimo caracter es coma? -> %s\n",  &s[ft_strlen(s) -1 ]);
	if (c == ',' && s[ft_strlen(s) - 1]  == ',')
        return (0); //Si estamos en la última línea y acaba en coma y no hay una línea vacía en el .rt hay que mirarlo.
	free_2d_array(temp);
	return (nbr_character);
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
    printf("Extract values\n");
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
					printf("salgoooo\2n");
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

int    check_range_vect(t_vect v)
{
    if (v.x > 1 || v.y > 1 || v.z > 1)
		return (1);
	if (v.x < -1 || v.y < -1 || v.z < -1)
		return (1);
    return (0);
}

int  check_range_color(t_color c)
{
    if (c.r > 255 || c.g > 255 || c.b > 255)
		return (1);
	if (c.r < 0 || c.g < 0 || c.b < 0)
		return (1);
    printf("rgb %f\n", c.g); 
    return (0);
}
int check_ranges(void *tmp, char obj)
{
	if (obj == 'C' && check_range_vect(((t_camera *)tmp)->n_vec))
		return (1);
	if (obj == 'A' && check_range_color(((t_amb_light *)tmp)->rgb))
		return (1);
	if (obj == 'L' && check_range_color(((t_light *)tmp)->rgb))
		return (1);
	if (obj == 'p' && (check_range_vect(((t_plane *)tmp)->n_vec) || check_range_color(((t_plane *)tmp)->rgb)))
		return (1);
	if (obj == 's' && (check_range_color(((t_sphere *)tmp)->rgb)))
		return (1);
	if (obj == 'c' && (check_range_vect(((t_cylinder *)tmp)->n_vec) || check_range_color(((t_cylinder *)tmp)->rgb)))
		return (1);
	return (0);
}
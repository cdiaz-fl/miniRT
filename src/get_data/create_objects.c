
#include "../../includes/miniRT.h"

t_camera	create_camera(char *s, t_world *all, int fd)
{
	t_camera	new;

	if (check_character(s,',') != 5 || check_character(s, ' ') < 4)
		wrong_values_handling(&s, all, fd, 5);
	//if (all->cam->pos->x)	Comprobar que solo h->y una cámara
	//	wrong_values_handling(s, all);
	new.pos.x = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	new.pos.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	new.pos.z = ft_atof(++s, 10);
	s = ft_strchr(s, ' ');

	new.n_vec.x = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	new.n_vec.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	new.n_vec.z = ft_atof(++s, 10);
	s = ft_strchr(s, ' ');

	new.FOV = ft_atoi(++s);
	if (check_ranges((void *)&new, 'C') || new.FOV > 180 || new.FOV < 0)
		wrong_values_handling(&s, all, fd, 5);
	return	new;
}

t_amb_light	create_amblight(char *s, t_world *all, int fd)
{
	t_amb_light	new;


	if (check_character(s,',') != 3 || check_character(s, ' ') < 3)
		wrong_values_handling(&s, all, fd, 5);
	s++;
	while (s && *s == ' ')
		s++;
	new.rate = ft_atof(s, 10);
	while (s && *s != ' ')
		s++;
	new.rgb.r = (double)ft_atoi(++s) / 255;
	while (s && *s != ',')
		s++;
	new.rgb.g = (double)ft_atoi(++s) / 255;
	while (s && *s != ',')
		s++;
	new.rgb.b = (double)ft_atoi(++s) / 255;
	if (check_ranges((void *)&new, 'A'))
		wrong_values_handling(&s, all, fd, 5);
	return	new;
}

t_light	create_light(char *s, t_world *all, int fd)
{
	t_light	new;

	//if (all->cam->pos->x)	Comprobar que solo h->y una cámara
	//	wrong_values_handling(s, all);
	if (check_character(s,',') != 5 || check_character(s, ' ') < 4)
		wrong_values_handling(&s, all, fd, 5);
	s++;
	while (s && *s == ' ')
		s++;
	new.position.x = ft_atof(s, 10);
	s = ft_strchr(s, ',');
	new.position.y = ft_atof(++s, 10);
	s = ft_strchr(s, ',');
	new.position.z = ft_atof(++s, 10);
	s = ft_strchr(s, ' ');
	new.brightness = ft_atof(s, 10);
	while (s && *s == ' ')
		s++;
	s = ft_strchr(s, ' ');
	//El color de la luz es solo para el bonus. Asique habra que quitar esto
	new.rgb.r = (double)ft_atoi(++s) / 255;
	new.intensity.r = 1 * new.brightness ;
	while (s && *s != ',')
		s++;
	new.rgb.g = (double)ft_atoi(++s) / 255;
	new.intensity.g = 1 * new.brightness;
	while (s && *s != ',')
		s++;
	new.rgb.b = (double)ft_atoi(++s) / 255;
	new.intensity.b = 1 * new.brightness;
	if (check_ranges((void *)&new, 'L'))
		wrong_values_handling(&s, all, fd, 5);
	return new;
}


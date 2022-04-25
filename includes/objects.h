
#ifndef	OBJECTS_H
# define OBJECTS_H

typedef struct s_camera
{
	double	x;
	double	y;
	double	z;
	
	double	nov_x;	//Normalized Orientation Vector 
	double	nov_y;
	double	nov_z;	//[-1.0 - 1.int	double	FOV; //Field Of View [0 - 180] No puede ser con decimales
}t_camera;

typedef struct s_amb_light
{
	double	rate;	//[0.0 - 1.0]

	int	r;	//[0 - 255]
	int	g;
	int	b;
}t_amb_light;


typedef struct s_light
{
	double	x;
	double	y;
	double	z;

	double	glow;	//[0.0 - 1.0]

	int	r;	//[0 - 255]
	int	g;
	int	b;
}t_light;

typedef struct s_sphere
{
	double	x;	//El punto describe el centro de la esfera
	double	y;
	double	z;

	double	diameter;

	int	r;	//[0 - 255]
	int	g;
	int	b;
}t_sphere;

typedef struct s_plane
{
	double	x;
	double	y;
	double	z;
	
	double	nov_x;	//Normalized Orientation Vector 
	double	nov_y;
	double	nov_z;	//[-1.0 - 1.0]

	int	r;	//[0 - 255]
	int	g;
	int	b;
}t_plane;

typedef struct s_cylinder
{
	double	x;
	double	y;
	double	z;

	double	nov_x;	//Normalized Orientation Vector 
	double	nov_y;
	double	nov_z;	//[-1.0 - 1.0]

	double	diameter;
	double	height;

	int	r;	//[0 - 255]
	int	g;
	int	b;
}t_cylinder;

typedef struct s_objects
{
	t_camera	cam;		//Solo puede haber una
	t_amb_light	a_light;		//Solo puede haber una
	t_light		light;		//Solo puede haber una
	t_sphere	*sphs;
	t_plane		*plns;
	t_cylinder	*cyls;
	unsigned int	sphs_nb;
	unsigned int	plns_nb;
	unsigned int	cyls_nb;
}t_objects;

int	create_amblight(char *line, t_objects *all);


#endif

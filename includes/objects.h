
#ifndef	OBJECTS_H
# define OBJECTS_H

# include "matrix.h"
# include "point_vector.h"
# include "stdbool.h"

typedef struct s_color
{
	double	r;	//[0 - 255]
	double	g;
	double	b;
}t_color;

typedef struct s_camera
{
	t_point	pos;		//Position
	t_vect	n_vec;	//Normalized Orientation Vector [-1.0 - 1.0]
	double	FOV; 				//Field Of View [0 - 180] Sin decimales
	double	pix_s;	//Pixel Size
	double	half_w;
	double	half_h;
	t_mtx		transform;
}t_camera;

typedef struct s_amb_light
{
	double	rate;	//[0.0 - 1.0]

	t_color	rgb;

}t_amb_light;


typedef struct s_light
{
	t_color diffuse;
    t_color ambient;
    t_color specular;
	t_point	position;	//Position
	t_color intensity; // color = (1, 1, 1) * brightness -> blanco * brightnees
    double      brightness;
	
	double	glow;	//[0.0 - 1.0]
	t_color	rgb;	//[0 - 255]
}t_light;
/*typedef struct  s_light2
{
    t_color diffuse;
    t_color ambient;
    t_color specular;

    t_point position;

    t_color intensity; // color = (1, 1, 1) * brightness -> blanco * brightnees
    double      brightness;
}t_light2;*/
typedef struct s_sphere
{
	t_point		pos;	//Centro de la esfera

	double	diameter;
	t_mtx	transform;	//Por defecto es la identity matrix
	t_mtx	inverse;	//Inversa de la trasnformada
	t_mtx	transpose;	//Traspuesta de la inversa
	
	t_color	rgb;	//[0 - 255]
	struct s_sphere	*next;
}t_sphere;

typedef struct s_plane
{
	t_point	pos;	//Position
	
	t_vect	n_vec;	//Normalized Orientation Vector 
			//[-1.0 - 1.0]

	t_color	rgb;	//[0 - 255]
	struct s_plane	*next;
}t_plane;

typedef struct s_cylinder
{
	t_point	pos;	//Position

	t_vect	n_vec;	//Normalized Orientation Vector 
			//[-1.0 - 1.0]

	double	diameter;
	double	height;

	t_color	rgb;	//[0 - 255]
	struct s_cylinder	*next;
}t_cylinder;

typedef struct s_world
{
	t_camera	cam;		//Solo puede haber una
	t_amb_light	a_light;	//Solo puede haber una
	t_light		light;		//Solo puede haber una
	t_sphere	*sphs;
	t_plane		*plns;
	t_cylinder	*cyls;
}t_world;

typedef struct s_computations
{
	char	obj_type;
	void	*object;
	double	t;
	t_point	point;
	t_vect	eyev;
	t_vect	normalv;
	bool	inside;
}t_comps;

t_camera	create_camera(char *s, t_world *all);
t_amb_light	create_amblight(char *s, t_world *all);
t_light	create_light(char *s, t_world *all);
void	create_planes(char *s, t_world *all);
void	create_spheres(char *s, t_world *all);
void	create_cylinders(char *s, t_world *all);


#endif

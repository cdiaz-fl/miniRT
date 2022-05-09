
#ifndef	OBJECTS_H
# define OBJECTS_H

# include "matrix.h"
# include "point_vector.h"
# include "stdbool.h"

typedef struct s_color
{
	double	r;	//[0 - 255 ]
	double	g;
	double	b;
}t_color;

typedef struct s_camera
{
	t_point	pos;	//Position
	t_vect	n_vec;	//Normalized Orientation Vector [-1.0 - 1.0]
	double	FOV; 		//Field Of View [0 - 180] Sin decimales, lo pongo double para poder pasarlo a radianes luego
	double	pix_s;
	double	half_w;
	double	half_h;
	t_mtx	transform;
	t_mtx	invert;
}t_camera;

typedef struct s_amb_light
{
	double	rate;	//[0.0 - 1.0]
	t_color	rgb;

}t_amb_light;

typedef struct s_light
{
	t_point		position;	//Position
	t_color 	diffuse;	//Calcular en lighting
    t_color 	specular;	//Calcular en lighting
    t_color 	ambient;	//t_amb_light.rate * t_amb_light.rgb
	t_color 	intensity;	// color = (1, 1, 1) * brightness -> blanco * brightnees
    double      brightness;	//Parámetro entrada t_light L.
	t_color		rgb;		//Bonus -> [255, 255, 255]
}t_light;

typedef struct s_sphere
{
	t_point		pos;	//Centro de la esfera

	double	diameter;
	t_mtx	transform;	//Por defecto es la identity matrix
	t_mtx	inverse;	//Inversa de la trasnformada
	t_mtx	transpose;	//Traspuesta de la inversa
	t_color	rgb;		//[0 - 255]
	struct s_sphere	*next;
}t_sphere;

typedef struct s_plane
{
	t_mtx	transform;	//Por defecto es la identity matrix
	t_mtx	inverse;	//Inversa de la trasnformada
	t_point	pos;	//Position
	t_vect	n_vec;	//Normalized Orientation Vector //[-1.0 - 1.0]
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

	t_mtx	transform;	//Por defecto es la identity matrix
	t_mtx	inverse;	//Inversa de la trasnformada
	t_mtx	transpose;	//Traspuesta de la inversa
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
	t_point	over_point; //Para calcular la sombra y que no haga un self-shadowing (salen puntos negros).
	t_vect	eyev;
	t_vect	normalv;
	bool	inside;
}t_comps;

/*Create_objects.c, cylinders.c, planes.c, shperes.c*/
t_camera	create_camera(char *s);
t_amb_light	create_amblight(char *s);
t_light		create_light(char *s);
void		create_planes(char *s, t_world *all);
void		create_spheres(char *s, t_world *all);
void		create_cylinders(char *s, t_world *all);

//Preparar las matrices de todos los objetos para hacer el cambio de mundo
void		prepare_object_transformations(t_world *world);

#endif

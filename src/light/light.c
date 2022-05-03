/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:43:51 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/03 15:18:06 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//normal_sphere -> Devuelve el vector NORMAL en el punto en el que intersecciona el rayo con una esfera.
//reflect_vect -> Vector que refleja la luz en una superficie.

#include "../../includes/miniRT.h"

t_vect	get_normal_sphere(t_sphere s, t_point world_point)
{
	t_vect center_surface_distance;
	
	//1. Convertimos el punto en el que intersecta el rayo con el objeto, del mundo real al mundo dek objeto
	t_point object_point = mul_point_mtx(&s.inverse, world_point);
	//2. Calculamos el vector NORMAL en el mundo del obj, restando el punto de la interseccion con el centro de la esfere
	t_vect object_normal = sub_point_point(object_point, create_point(0, 0, 0));

	//3. Convertimos el vector NORMAL al mundo real.
	t_vect world_normal = mul_vect_mtx(&s.transpose, object_normal);

	//4. En el libro poene la dimension w = 0, nosotros no lo tenemos que hacer.
	
	//5. Normalizamos el vector
	return (normalization_vect(world_normal));
}

t_vect	get_reflect_vect(t_vect light_vect, t_vect normal_vect)
{
	//1. Calculamos el angulo entre el vector in(el de la luz), y la NORMAL
	double angle = dot_product_vect(light_vect, normal_vect);
	
//	printf("angulo -> %f\n", angle);
	//2. lo multiplicamos por la normal y por 2
	t_vect temp = scalar_mul_vect(normal_vect, (angle * 2));

	//3. Restar todo al vector de la luz
	return (sub_vect_vect(light_vect, temp));
}

//lighting 
//OBJETIVO -> Calculamos el color final
//Para ello hay que SUMAR (light.ambient + light.diffuse + light.specular)
//	Datos que no sabemos -> light.diffuse y light.specular
//
//PARAMETROS DE ENTRADA:
//World point -> Interseccion del rayo-objeto.
//
//Datos que necesitamos:
//	- Luz: 
//		intensidad
//		punto de origen
//	- Material:
//		Color
//		Ambient light
//		*material.shininess
//		*material specular
//		*material diffusse
//	-Punto en el que interseca el rayo-objeto.(World_point?)
//	-Vector Normal en el punto de interseccion
//	-Eye vect -> Sera el vector del Rayo desde la camara en negativo.
//	-Vector Reflection -> Se calcula dentro de la función.
//
//	Duda: Diferencia entre el color ambiental y el color de la esfera. 
//	Duda2: Nos faltan datos -> No nos los dan
//		material.shininess = 200.0 defecto
//		material specular = 0.9
//		material diffusse = 0.9
//
//RETURN:
//		Color del objeto -> La suma de;
//		light.ambient (Depende light.intensity, material.color, material.ambient)
//
/*t_vect	lighting(t_light light, void *material, t_point world_point, t_vect normal_vect, t_vect ray_vect)
{
	//1. Calculamos el color de la superficie con el brillo de la luz.
	t_color 	effective_color  = scalar_mul_color(material.color, light.intensity);
	
	
	//2. Calcular la dirección de la fuente de luz.
	//Lo tendriamos que haber calculado para calcular el reflect_vect. Se podria guardar en la estrucutra de la luz.
	t_vect	light_vect = normalization_vect(sub_point_point(light.position, world_point));

	//3. Calcular el color teniendo en cuenta el effectie color y la luz ambiental
	//QUITAR?
	t_color ambient_color = scalar_mul_color(effective_color, material.ambient);

	//4. Calculamos la diffusion y specular [0, 1]
	//	4. 1. Angulo entre el vector de la luz y la normal.
	//	Lo tenemos calculado para calcular el reflect_vect. Se podria guardar en la estrucutra de la luz.
	//	IF 4. 2. Si el angulo en menos a cero, estamos al otro lado de la superficie.
	double	angle_light_normal = dot_product_vect(light_vect, normal_vect);
		t_vect
	if (angle_light_normal < 0)
	{
		light.diffuse = create_color(0, 0, 0); //Donde guardamos esto???
		light.specular = create_color(0, 0 ,0);
		}
	else
	{
		//ELSE 4. 3. DIFFUSION //Material difusse no nos lo dan!!!
		light.diffuse =  scalar_mul_color(effective_color, angle_light_normal);
		//QUITAR?
		//light.diffuse = scalar_mul_color(light.diffuse, material.diffuse);
		//4. 4 SPECULAR
        t_vect reflected_vect = get_reflect_vect(neg_vect(light_vect), normal_vect);
        double angle_reflect_camera = dot_product_vect(reflected_vect, neg_vect(ray_vect));
		if (angle_reflect_camera <= 0)
            light.specular = create_color(0,0,0);
		else
		{
			//QUITAR?
			double factor = pow(angle_reflect_camera, material.shininess);
            light.specular =  scalar_mul_color(light.intensity,   materia.specular* factor);
		}
	}
    return (add_color_color(light.specular, (add_color_color(light.ambient, light.diffuse))));
}*/

t_color  lighting2(t_light light,t_sphere s, t_point world_point, t_vect normal_vect, t_vect ray_vect)
{
  //  t_color     effective_color  = mul_color_color(create_color(1, 0.2, 1), light.intensity); //s.color -> 0, 1, 0
    t_color     effective_color  = mul_color_color(s.rgb, light.intensity); //s.color -> 0, 1, 0

    t_vect  light_vect = normalization_vect(sub_point_point(light.position, world_point));

 //   light.ambient = scalar_mul_color(effective_color, 0.1); //0.9 s-> s.ambient

    double  angle_light_normal = dot_product_vect(light_vect, normal_vect);
    if (angle_light_normal < 0)
	{
        light.diffuse = create_color(0, 0, 0); 
        light.specular = create_color(0, 0 ,0);
	}
    else
    {
        light.diffuse =  scalar_mul_color(effective_color, angle_light_normal);
        light.diffuse = scalar_mul_color(light.diffuse, 0.9);
        t_vect reflected_vect = get_reflect_vect(neg_vect(light_vect), normal_vect);
        double angle_reflect_camera = dot_product_vect(reflected_vect, neg_vect(ray_vect));
        if (angle_reflect_camera <= 0)
            light.specular = create_color(0,0,0);
        else
        {
            double factor = pow(angle_reflect_camera, 200); //200 -> materila.shinies
            light.specular =  scalar_mul_color(light.intensity,  (0.9 * factor));
			static int i;
			if (++i < 4)
			{
			printf("\nsphere r[%f], g[%f], b[%f] angle = %f\n", s.rgb.r, s.rgb.g, s.rgb.b, factor);
			printf("brighness %f\n", light.brightness);	
			printf("intensity [%f], g[%f], b[%f] angle = %f\n", light.intensity.r, light.intensity.g, light.intensity.b, factor);
			printf("efectiver r[%f], g[%f], b[%f] angle = %f\n", effective_color.r, effective_color.g, effective_color.b, factor);
			printf("ambient r[%f], g[%f], b[%f] angle = %f\n", light.ambient.r, light.ambient.g, light.ambient.b, factor);
			printf("specular r[%f], g[%f], b[%f] angle = %f\n", light.specular.r, light.specular.g, light.specular.b, factor);
			printf("difusse r[%f], g[%f], b[%f] angle = %f\n", light.diffuse.r, light.diffuse.g, light.diffuse.b, angle_reflect_camera);
		
			}
		}
    }
	t_color c = add_color_color(light.specular, (add_color_color(light.ambient, light.diffuse)));
//	check_max_color(&c);
    return (c);
}
































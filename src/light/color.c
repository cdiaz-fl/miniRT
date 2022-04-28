/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:05:01 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/28 14:29:28 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/miniRT.h"

int	convert_color_to_int(t_color c)
{
  
	int color;
	
//	color	= ((int)((255.999 * c.r) << 16)/255.999) + ((int)(255.999 * c.g) << 8) + ((int)(255.999 * c.b));
	color	= ((int)(255 * c.r) << 16) + ((int)(255 * c.g) << 8) + ((int)(255 * c.b));
	return (color);
//	color	= (c.r << 16) + (c.g << 8) + ( c.b);
//	int rgb = ((c.r & 0x0ff) << 16) | ((c.g & 0x0ff) << 8)| (c.b & 0x0ff);
//	int rgb = 65536 * c.r + 256 * c.g + c.b;
//	return (rgb);
}

void	check_color_range(t_color c)
{
	if (c.r < 0 || c.r > 1 || c.g < 0 || c.g > 1 || c.b < 0 || c.b > 1)
	{
		printf("Error color\n");
		exit(1);
	}
}

t_color		create_color(double red, double green, double blue)
{
	t_color new;
	
	new.r = red;
	new.g = green;
	new.b = blue;
	return (new);
}
t_color	scalar_mul_color(t_color color, double scalar)
{
	t_color new;

	new.r = color.r * scalar;
	new.g = color.g * scalar;
	new.b = color.b * scalar;
	check_max_color(&new);
	return (new);
}

t_color mul_color_color(t_color c1, t_color c2)
{
	t_color new;

	new.r = c1.r * c2.r;
	new.g = c1.g * c2.g;
	new.b = c1.b * c2.b;
/*	new.r = (int)(c1.r / 255 * c2.r);
	new.g = (int)(c1.g / 255 * c2.g);
	new.b = (int)(c1.b / 255 * c2.b) ;*/
	check_max_color(&new);
	return (new);
}

t_color add_color_color(t_color c1, t_color c2)
{
	t_color new;

	new.r = c1.r + c2.r;
	new.g = c1.g +	c2.g;
	new.b = c1.b + c2.b;
	check_max_color(&new);
	return (new);
}

void	check_max_color(t_color *c)
{
	if (c->r > 1 )
		c->r = 1;
	if (c->r < 0)
		c->r = 0;
	if (c->g > 1 )
		c->g = 1;
	if (c->g < 0)
		c->g = 0;
	if (c->b > 1 )
		c->b = 1;

/*	if (c->r > 255 )
		c->r = 255;
	if (c->r < 0)
		c->r = 0;
	if (c->g > 255 )
		c->g = 255;
	if (c->g < 0)
		c->g = 0;
	if (c->b > 255 )
		c->b = 255;
	if (c->b < 0)
		c->b = 0;*/
}

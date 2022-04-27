/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:05:01 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/27 16:15:52 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/miniRT.h"

int	convert_color_to_int(t_color c)
{
  
	int color;
	
	color	= ((int)(255.999 * c.r) << 16) + ((int)(255.999 * c.g) << 8) + ((int)(255.999 * c.b));
	return (color);
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
	return (new);
}

t_color mul_color_color(t_color c1, t_color c2)
{
	t_color new;

	new.r = c1.r * c2.r;
	new.g = c1.g * c2.g;
	new.b = c1.b * c2.b;
	return (new);
}

t_color add_color_color(t_color c1, t_color c2)
{
	t_color new;

	new.r = c1.r + c2.r;
	new.g = c1.g +	c2.g;
	new.b = c1.b + c2.b;
	return (new);
}

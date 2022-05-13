/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 08:22:38 by zcanales          #+#    #+#             */
/*   Updated: 2022/05/13 08:22:40 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"
/*    % Automated normalization
    if minVec >= 0
        % Normalize between 0 and 1
        vecN = (vec - minVec)./( maxVec - minVec );
        vecD = minVec + vecN.*(maxVec - minVec);
    elseif maxVec <= 0
        % Normalize between -1 and 0
        vecN = (vec - maxVec)./( maxVec - minVec );
        vecD = maxVec + vecN.*(maxVec - minVec);
    else
        % Normalize between -1 and 1
        vecN = ((vec-minVec)./(maxVec-minVec) - 0.5 ) *2;
        vecD = (vecN./2+0.5) * (maxVec-minVec) + minVec;
    end*/
static double	min_normalization(t_vect v)
{
	double min = 0;
	
	if (v.x <= v.y)
		min = v.x;
	else
		min = v.y;
	if (v.z <= min)
		min = v.z;
	return (min);
}

static double	max_normalization(t_vect v)
{
	double max = 0;

	if (v.x >= v.y)
		max = v.x;
	else
		max = v.y;
	if (v.z >= max)
		max = v.z;
	return (max);
}

t_vect	ft_normalization(t_vect v)
{
	t_vect normal;
	double	range;
	double min;
	double max;

	min = min_normalization(v);
	max = max_normalization(v);
	range = max - min;
	normal = create_vect(v.x - min, v.y - min, v.z - min);
	if (min >= 0)
		normal = scalar_div_vect(normal, range);
	else if (max <= 0)
	{
		normal = create_vect(v.x - max, v.y - max, v.z - max);
		normal = scalar_div_vect(normal, range);
	}
	else
	{
		normal = scalar_div_vect(normal, range);
		normal.x -= 0.5;
		normal.y -= 0.5;
		normal.z -= 0.5;
		normal = scalar_mul_vect(normal, 2);
	}
	return (normal);
}
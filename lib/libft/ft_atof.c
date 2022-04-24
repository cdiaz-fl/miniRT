/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:16:37 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/22 13:53:36 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"
#include <stdio.h>
float	ft_atof(char *s)
{
	int first;
	int decimal;
	int	i;
	int	len;

	len = 0;
	first = ft_atoi(&s[0]);
	i = -1;
	decimal = 0;
	while (s[++i])
	{
		if (s[i] == '.')
		{
			i++;
			decimal = ft_atoi(&s[i]);
			while (s[i] && ft_isdigit(s[i]))
			{
				len++;
				i++;
			}
			return ((float)first + decimal / pow(10, len));
		}
	}
	return ((float)first + decimal);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:16:37 by zcanales          #+#    #+#             */
/*   Updated: 2022/04/26 08:53:49 by cdiaz-fl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"
#include <stdio.h>

double	ft_atof(char *s, float base)
{
	double	sum;
	double	rest;
	double	neg;
	int	i;

	sum = 0.0;
	rest = 0.0;
	i = 0;
	neg = 1.0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '+')
		i++;
	else if (s[i] == '-' && ++i)
		neg = -1.0;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
		sum = (sum * base) + (double)(s[i++] - '0');
	if (s[i] && s[i] == '.')
		i++;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		rest += (double)(s[i++] - '0') / base;
		base *= 10;
	}
	return ((sum + rest) * neg);
}

/*
 *
 *REVISAR LOS NEGATIVOS
 *
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


int main()
{
	printf("Atof = %.5f,  Charly = %.5f    Zaloa = %.5f\n", atof("100"), ft_atof("100", 10), ft_zaloa("100"));
	printf("Atof = %.5f,  Charly = %.5f    Zaloa = %.5f\n", atof("1.5"), ft_atof("1.5", 10), ft_zaloa("1.5"));
	printf("Atof = %.5f,  Charly = %.5f   Zaloa = %.5f\n", atof("+1.5"), ft_atof("+1.5", 10), ft_zaloa("+1.5"));
	printf("Atof = %.5f,  Charly = %.5f   Zaloa = %.5f\n", atof("-1.5"), ft_atof("-1.5", 10), ft_zaloa("-1.5"));
	printf("Atof = %.4f,  Charly = %.5f   Zaloa = %.5f\n", atof("104.3213"), ft_atof("104.3213", 10), ft_zaloa("104.3213"));
	printf("Atof = %.5f,  Charly = %.5f   Zaloa = %.5f\n", atof("+104.3"), ft_atof("+104.3", 10), ft_zaloa("+104.3"));
	printf("Atof = %.5f,  Charly = %.5f   Zaloa = %.5f\n", atof("-104.3"), ft_atof("-104.3", 10), ft_zaloa("-104.3"));
	printf("Atof = %.5f,  Charly = %.5f   Zaloa = %.5f\n", atof("9007199254740991"), ft_atof("9007199254740991", 10), ft_zaloa("9007199254740991"));
	printf("Atof = %.5f,  Charly = %.5f   Zaloa = %.5f\n", atof("-9007199254740991"), ft_atof("-9007199254740991", 10), ft_zaloa("-9007199254740991"));
}

*/

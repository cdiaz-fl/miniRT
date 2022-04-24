
#include <stdlib.h> //Atof
#include <stdio.h> //Printf
#include <math.h> //nan

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

//Pruebas Atof
int main()
{
	printf("Atof = %.2f,  Ft_Atof = %.2f\n", atof("100"), ft_atof("100", 10));
	printf("Atof = %.2f,  Ft_Atof = %.2f\n", atof("1.5"), ft_atof("1.5", 10));
	printf("Atof = %.2f,  Ft_Atof = %.2f\n", atof("+1.5"), ft_atof("+1.5", 10));
	printf("Atof = %.2f,  Ft_Atof = %.2f\n", atof("-1.5"), ft_atof("-1.5", 10));
	printf("Atof = %.4f,  Ft_Atof = %.4f\n", atof("104.3213"), ft_atof("104.3213", 10));
	printf("Atof = %.2f,  Ft_Atof = %.2f\n", atof("+104.3"), ft_atof("+104.3", 10));
	printf("Atof = %.2f,  Ft_Atof = %.2f\n", atof("-104.3"), ft_atof("-104.3", 10));
	printf("Atof = %.2f,  Ft_Atof = %.2f\n", atof("9007199254740991"), ft_atof("9007199254740991", 10));
	printf("Atof = %.2f,  Ft_Atof = %.2f\n", atof("-9007199254740991"), ft_atof("-9007199254740991", 10));
	printf("Atof = %.2f,  Ft_Atof = %.2f\n", atof("1.5, 10"), ft_atof("1.5", 10));
	printf("Atof = %.2f,  Ft_Atof = %.2f\n", atof("1.5, 10"), ft_atof("1.5", 10));

}

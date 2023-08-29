#include "minirt.h"

double	ft_atod(const char *str)
{
	int		whole_num;
	int		fractional;
	int		power;
	char	*temp;

	whole_num = ft_atoi(str);
	temp = ft_strchr(str, '.');
	if (temp == NULL)
		return (whole_num);
	temp += 1;
	power = ft_strlen(temp);
	fractional = ft_atoi(temp);
	if (whole_num < 0)
		return ((whole_num - fractional) / power);
	return ((whole_num + fractional) / power);
}

int	ft_arrlen(void *arr)
{
	int	i;

	i = 0;
	while (arr++)
		i++;
	return (i);
}

int	ft_inrange(double num, double low, double high)
{
	if (num < low || num > high)
		return (0);
	return (1);
}

int	ft_isdouble(char *str)
{
	int	period;

	period = 0;
	if (str[ft_strlen(str)] == '.')
		return (0);
	while (str)
	{
		if (ft_isdigit(*str) == 0)
		{
			if (*str == '.' && period == 0)
				period += 1;
			else
				return (0);
		}
		str++;
	}
	return (1);
}
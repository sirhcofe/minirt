/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:04:32 by jthor             #+#    #+#             */
/*   Updated: 2023/09/13 20:04:34 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (power == 0)
		return (whole_num);
	fractional = ft_atoi(temp);
	if (str[0] == '-')
		return (whole_num - (double)(fractional / pow(10, power)));
	return (whole_num + (double)(fractional / pow(10, power)));
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
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
	if (str[0] == '+' || str[0] == '-')
		str++;
	while (*str)
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

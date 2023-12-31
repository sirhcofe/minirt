/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:04:57 by jthor             #+#    #+#             */
/*   Updated: 2023/09/13 20:04:59 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_isrgb(char *str)
{
	int	comma_cnt;
	int	i;

	comma_cnt = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			if (str[i] == ',')
				comma_cnt += 1;
			else
				return (0);
		}
	}
	if (comma_cnt != 2)
		return (0);
	return (1);
}

void	set_coord(t_coord *obj, double x, double y, double z)
{
	obj->x = x;
	obj->y = y;
	obj->z = z;
	obj->w = 1.0;
}

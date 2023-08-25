#include "minirt.h"

int	ft_isrgb(char *str)
{
	int	comma_cnt;
	int i;

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
	return(1);
}

void	set_coord(t_coord *obj, double *temp)
{
	obj->x = temp[0];
	obj->y = temp[1];
	obj->z = temp[2];
	obj->w = 1.0;
}
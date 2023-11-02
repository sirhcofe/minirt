#include <minirt.h>

void	print_image(t_minirt *rt)
{
	t_coord	*ray_vector;
	size_t	ctr;
	int		index;

	if (rt->file_data->objects != NULL)
	{
		ctr = -1;
		while (++ctr < (rt->height * rt->width))
		{
			ray_vector = get_ray_vector(rt, ctr);
			index = get_touchy(rt->file_data, ray_vector);
			if (index == -1)
				void_pixel(rt, ctr);
			else
				colour_pixel(rt, ray_vector, index, ctr);
			free(ray_vector);
		}
	}
	else
		empty_protocol(rt);
}



int	get_touchy(t_data *f_data, t_coord *ray_vector)
{
	int			ret;
	int			curr;
	double		closest_dist;
	double		curr_dist;
	t_list		*lst;
	t_object	*node;

	ret = -1;
	curr = 0;
	closest_dist = INFINITY;
	lst = f_data->objects;
	while (lst)
	{
		// typecast so that I can use it.
		node = (t_object *)lst->content;

		// use correct function for current formula to get the current distance.
		if (node->e_idx == sp)
			curr_dist = get_sp_dist(*ray_vector, f_data->camera.point, &node->obj.sphere);
		else if (node->e_idx == pl)
			curr_dist = get_pl_dist(*ray_vector, f_data->camera.point, &node->obj.plane);
		else
			curr_dist = get_sp_dist(*ray_vector, f_data->camera.point, &node->obj.sphere);

		// compare if the current object is closer.
		if (curr_dist < closest_dist)
		{
			ret = curr;
			closest_dist = curr_dist;	
		}

		// next object
		curr++;
		lst = lst->next;
	}
	return (ret);
}
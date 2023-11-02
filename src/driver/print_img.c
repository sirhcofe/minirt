/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:01:41 by jthor             #+#    #+#             */
/*   Updated: 2023/10/25 09:36:03 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// WIP : Figure out the image height and width

void	print_image(t_minirt *rt)
{
	t_coord	*ray_vector;
	size_t	ctr;
	int		index;

	if (rt->file_data->num_sp + rt->file_data->num_pl + rt->file_data->num_cy)
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

/**
 * data[] ;
 * data[0] -> index to return, should be the index of the closest obj. -1 if no intersection
 * data[1] -> index counter, use to keep track of which objet we looking at.
 * data[2] -> distance between the closest object and the camera.
 */

int	get_touchy(t_data *f_data, t_coord *ray_vector)
{
	double		data[3];
	t_intrsct	temp;

	data[0] = -1;
	data[1] = 0;
	temp.r_vect = *ray_vector;
	temp.cam_pt = f_data->camera.point;
	temp.obj_lst = f_data->spheres;
	if (f_data->num_sp)
		scroll_obj(&data, temp, get_sp_dist);
	temp.obj_lst = f_data->planes;
	if (f_data->num_pl)
		scroll_obj(&data, temp, get_pl_dist);
	temp.obj_lst = f_data->cylinders;
	if (f_data->cylinders)
		scroll_obj(&data, temp, get_cy_dist);
	return ((int)(data[0]));
}

void	empty_protocol(t_minirt *rt)
{
	size_t	ctr;
	int		colour;

	ctr = -1;
	while (++ctr < (rt->height * rt->width))
		void_pixel(rt, ctr);
}

void	scroll_obj(double *data[3], t_intrsct i_data,
			int (*f)(double *, t_coord, t_coord, void *))
{
	double	dist_res;

	while (i_data.obj_lst)
	{
		if ((*f)(&dist_res, i_data.r_vect,
			i_data.cam_pt, i_data.obj_lst->content))
		{
			if (*data[0] == -1)
			{
				*data[0] = *data[1];
				*data[2] = dist_res;
			}
			else
			{
				if (dist_res < *data[2])
				{
					*data[0] = *data[1];
					*data[2] = dist_res;
				}
			}
		}
		*data[1] += 1;
		i_data.obj_lst = i_data.obj_lst->next;
	}
}

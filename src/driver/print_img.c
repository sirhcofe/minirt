/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 20:19:22 by jthor             #+#    #+#             */
/*   Updated: 2023/11/03 20:19:24 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	print_image(t_minirt *rt)
{
	t_coord	ray_vector;
	size_t	ctr;
	int		index;

	if (rt->file_data->objects != NULL)
	{
		ctr = -1;
		while (++ctr < (rt->height * rt->width))
		{
			ray_vector = get_ray_vector(rt, rt->file_data->camera, ctr);
			index = get_touchy(rt->file_data, ray_vector);
			if (index == -1)
				void_pixel(rt, rt->file_data->ambience.colour, ctr);
			else
				render_pixel(rt, index, ctr);
		}
	}
	else
		empty_protocol(rt);
}

void	empty_protocol(t_minirt *rt)
{
	size_t	ctr;
	int		colour;

	ctr = -1;
	while (++ctr < (rt->height * rt->width))
		void_pixel(rt, rt->file_data->ambience.colour, ctr);
}

double	get_curr_dist(t_coord r_vect, t_coord ray_ori, void *lst_content)
{
	t_object	*node;

	node = (t_object *)lst_content;
	if (node->e_idx == sp)
		return (sp_intersection(r_vect, ray_ori, &(node->obj.sphere)));
	else if (node->e_idx == pl)
		return (pl_intersection(r_vect, ray_ori, &(node->obj.plane)));
	else
		return (cy_intersection(r_vect, ray_ori, &(node->obj.cylinder)));
}

int	get_touchy(t_data *f_data, t_coord r_vect)
{
	int			ret;
	int			curr;
	double		closest_dist;
	double		curr_dist;
	t_list		*lst;

	ret = -1;
	curr = 0;
	closest_dist = INFINITY;
	lst = f_data->objects;
	while (lst)
	{
		curr_dist = get_curr_dist(r_vect, f_data->camera.point, lst->content);
		if (curr_dist < closest_dist)
		{
			ret = curr;
			closest_dist = curr_dist;	
		}
		curr++;
		lst = lst->next;
	}
	return (ret);
}

t_coord	get_ray_vector(t_minirt *rt, t_cam cam, size_t ctr)
{
	t_coord	offset;
	t_coord	ret;
	double	inc;
	int		x;
	int		y;

	x = ctr % rt->height;
	y = ctr / rt->height;
	inc = cam.fov / rt->width;
	offset = rotation(&cam.look, inc * (y - rt->height / 2), cam.right);
	ret = rotation(&offset, inc * (x - rt->width / 2), cam.up);
	return (normalize(ret));
}

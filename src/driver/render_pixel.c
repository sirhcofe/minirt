/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:27:48 by jthor             #+#    #+#             */
/*   Updated: 2023/11/06 14:27:49 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*get_object(t_list *obj_lst, int index)
{
	int	iter;

	iter = -1;
	while (++iter < index)
		obj_lst = obj_lst->next;
	return ((t_object *)obj_lst->content);
}

t_coord	get_intsct_point(t_object *node)
{
	if (node->e_idx == sp)
		return (node->obj.sphere.intsct);
	else if (node->e_idx == pl)
		return (node->obj.plane.intsct);
	else
		return (node->obj.cylinder.intsct);
}

double	calc_shade_factor(t_object *obj, t_coord intsct, t_coord to_light)
{
	t_coord	normal;

	if (obj->e_idx == sp)
		normal = normalize(vect_subt(intsct, obj->obj.sphere.center));
	else if (obj->e_idx == pl)
		normal = obj->obj.plane.normal_vector;
	else
		normal = get_cy_normal(obj->obj.cylinder, intsct);
	return (dot_prod(normal, to_light));
}

int	ft_inshadow(t_data *f_data, t_coord intsct_pt, int index, t_coord to_light)
{
	t_list	*lst;
	int		curr;
	double	dist_val;

	curr = 0;
	lst = f_data->objects;
	while (lst)
	{
		if (index == curr)
			continue ;
		dist_val = get_curr_dist(to_light, intsct_pt, lst->content);
		if (dist_val != INFINITY) // there is an object in the way
		{
			if (dist_val <= get_dist(intsct_pt, f_data->light.point))
				return (1);
			// else the "obstructing" object is behind the light, so technically not in shadow
		}
		curr++;
		lst = lst->next;
	}
	return (0);
}

render_pixel(t_minirt *rt, t_coord *ray_vector, int index, size_t ctr)
{
	t_object	*obj;
	t_coord		intsct_pt;
	t_coord		to_light;
	double		shade_factor;
	int			final_colour;

	obj = get_object(rt->file_data->objects, index);
	intsct_pt = get_intsct_point(obj);
	to_light = normalize(vect_subt(rt->file_data->light.point, intsct_pt));
	shade_factor = calc_shade_factor(obj, intsct_pt, to_light);
	if (ft_inshadow(rt->file_data, intsct_pt, index, to_light)) // there is an object in the way
		blend_shadow();
	else
		blend_light();
}

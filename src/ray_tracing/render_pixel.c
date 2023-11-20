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


double	calc_shade_factor(t_object *obj, t_coord intsct, t_coord to_light)
{
	t_coord	normal;
	double	res;

	if (obj->e_idx == sp)
		normal = normalize(vect_subt(intsct, obj->obj.sphere.center));
	else if (obj->e_idx == pl)
		normal = obj->obj.plane.normal_vector;
	else
		normal = get_cy_normal(obj->obj.cylinder, intsct);
	res = dot_prod(normal, to_light);
	if (res < 0)
		return (0);
	return (res);
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
		if (index != curr)
		{
			dist_val = get_curr_dist(to_light, intsct_pt, lst->content);
			if (dist_val != INFINITY) // there is an object in the way
			{
				if (dist_val <= vect_magnitude(intsct_pt, f_data->light.point))
					return (1);
				// else the "obstructing" object is behind the light, so technically not in shadow
			}
		}
		curr++;
		lst = lst->next;
	}
	return (0);
}

int	blend(t_object *obj, t_rgb src, double shade_factor)
{
	t_rgb	obj_col;
	t_rgb	res;
	double	result;

	obj_col = get_colour(obj);
	res.red = (obj_col.red + src.red) * 0.5;
	res.green = (obj_col.green + src.green) * 0.5;
	res.blue = (obj_col.blue + src.blue) * 0.5;
	result = (double)(create_colour(0, res.red, res.green, res.blue));
	return ((int)(result * shade_factor));
}

void	render_pixel(t_minirt *rt, int index, size_t ctr)
{
	t_object	*obj;
	t_coord		intsct_pt;
	t_coord		to_light;
	double		shade_factor;
	int			final_clr;

	obj = get_object(rt->file_data->objects, index);
	intsct_pt = get_intsct_point(obj);
	to_light = normalize(vect_subt(rt->file_data->light.point, intsct_pt));
	shade_factor = calc_shade_factor(obj, intsct_pt, to_light);
	if (ft_inshadow(rt->file_data, intsct_pt, index, to_light)) // there is an object in the way
		final_clr = blend(obj, rt->file_data->light.colour, shade_factor);
	else
		final_clr = blend(obj, rt->file_data->ambience.colour, shade_factor);
	put_pxl(rt, ctr % rt->width, ctr / rt->width, final_clr);
}

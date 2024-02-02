/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 06:03:58 by jthor             #+#    #+#             */
/*   Updated: 2024/02/01 13:48:59 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Calculates the reflection vector given an incident vector and a normal vector
 * at the point of reflection.
 * @param i The normalized incident vector representing the incoming direction
 * of light or view vector.
 * @param n The normalized normal vector at the surface where the reflection
 * occurred.
 * @return The reflection vector calculated using the formula
 * R = I - 2 * (N · I) * N, where R is the reflection vector, I is the incident
 * vector, N is the normal vector, and (N · I) is the dot product of N and I.
*/
t_coord	reflect(t_coord i, t_coord n)
{
	t_coord	res;

	res.x = i.x - 2 * dot_prod(n, i) * n.x;
	res.y = i.y - 2 * dot_prod(n, i) * n.y;
	res.z = i.z - 2 * dot_prod(n, i) * n.z;
	return (res);
}

int	ft_inshadow(t_data *f_data, t_coord intsct_pt, int index, t_coord *vectors)
{
	t_list	*lst;
	int		curr;
	double	dist_val;

	curr = 0;
	lst = f_data->objects;
	while (lst)
	{
		// if (index != curr)
		// {
		// 	dist_val = get_curr_dist(vectors[to_light], intsct_pt, lst->content);
		// 	if (dist_val != INFINITY)
		// 	{
		// 		if (dist_val <= vect_magnitude(intsct_pt, f_data->light.point))
		// 			return (1);
		// 	}
		// }
		dist_val = get_curr_dist(vectors[to_light], intsct_pt, lst->content);
		if (dist_val != INFINITY)
		{
			if (dist_val <= vect_magnitude(intsct_pt, f_data->light.point))
				return (1);
		}
		curr++;
		lst = lst->next;
	}
	return (0);
}

void	calc_vect(t_minirt *rt, t_object *obj, t_coord *vectors, t_coord *intsct)
{
	vectors[to_light] = normalize(vect_subt(rt->file_data->light.point,
				*intsct));
	vectors[to_viewer] = normalize(vect_subt(rt->file_data->camera.point,
				*intsct));
	vectors[normal] = get_normal(obj, *intsct, vectors[from_camera]);
	*intsct = vect_add(*intsct, vect_mult(vectors[normal], SHADOW_BIAS));
	vectors[reflect_dir] = reflect(vect_mult(vectors[to_light], -1.0),
			vectors[normal]);
}

void	render_pixel(t_minirt *rt, int index, size_t ctr, t_coord ray_ori)
{
	t_object	*obj;
	t_rgb		obj_color;
	t_coord		intersect_pt;
	t_coord		vectors[5];
	t_rgb		final;

	obj = get_object(rt->file_data->objects, index);
	obj_color = get_colour(obj);
	intersect_pt = get_intsct_point(obj);
	vectors[from_camera] = ray_ori;
	calc_vect(rt, obj, vectors, &intersect_pt);
	if (ft_inshadow(rt->file_data, intersect_pt, index, vectors))
	{
		final.red = obj_color.red * rt->file_data->ambience.colour.red
			* rt->file_data->ambience.ratio * 255;
		final.green = obj_color.green * rt->file_data->ambience.colour.green
			* rt->file_data->ambience.ratio * 255;
		final.blue = obj_color.blue * rt->file_data->ambience.colour.blue
			* rt->file_data->ambience.ratio * 255;
	}
	else
		final = phong(rt, obj_color, vectors);
	put_pxl(rt, ctr % rt->width, ctr / rt->width,
		create_colour(0, final.red, final.green, final.blue));
}

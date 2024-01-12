/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:27:48 by jthor             #+#    #+#             */
/*   Updated: 2024/01/11 20:02:06 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



double	calc_sec_elem(t_coord cam, t_coord normal, t_coord intsct, t_coord to_light)
{
	t_coord	reflection;
	t_coord	point2cam;
	double	temp;

	temp = dot_prod(normal, to_light);
	if (temp < 0)
		temp = 0;
	reflection = vect_subt(vect_mult(normal, 2 * temp), to_light);
	reflection = normalize(reflection);
	point2cam = (normalize(vect_subt(cam, intsct)));
	return (pow(dot_prod(reflection, point2cam), 20));
}

int	phong_calc(t_data *f_data, int index, t_coord intsct, t_coord to_light)
{
	double	amb_elem;
	double	diff_elem;
	double	sec_elem;
	double	final_factor;
	t_coord	normal;
	t_rgb	light_res;
	t_object	*obj;

	normal = get_normal(obj, intsct, to_light);
	obj = get_object(f_data->objects, index);
	amb_elem = f_data->ambience.ratio;
	diff_elem = calc_shade_factor(obj, normal, to_light);
	sec_elem = calc_sec_elem(f_data->camera.point, normal, intsct, to_light);
	light_res.red = amb_elem * f_data->ambience.colour.red + (diff_elem + sec_elem) * f_data->light.colour.red;
	light_res.green = amb_elem * f_data->ambience.colour.green + (diff_elem + sec_elem) * f_data->light.colour.green;
	light_res.blue = amb_elem * f_data->ambience.colour.blue + (diff_elem + sec_elem) * f_data->light.colour.blue;
	if (ft_inshadow(f_data, intsct, index, to_light))
		return (blend(obj, light_res, 0.5, f_data->light.ratio));
	return (blend(obj, light_res, 1, f_data->light.ratio));
}

double	calc_shade_factor(t_object *obj, t_coord normal, t_coord to_light)
{
	double	res;

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

int	blend(t_object *obj, t_rgb illum, double shadow, double light_factor)
{
	t_rgb	obj_col;
	t_rgb	res;
	double	result;
	double	weight = 1 - light_factor;

	obj_col = get_colour(obj);
	res.red = (obj_col.red * weight + illum.red * light_factor);
	res.green = (obj_col.green * weight + illum.green * light_factor);
	res.blue = (obj_col.blue * weight + illum.blue * light_factor);
	result = create_colour(0, res.red * shadow, res.green * shadow, res.blue * shadow);
	return (result);
}

void	render_pixel(t_minirt *rt, int index, size_t ctr)
{
	t_object	*obj;
	t_coord		intsct_pt;
	t_coord		to_light;
	// double		shade_factor;
	int			final_clr;

	obj = get_object(rt->file_data->objects, index);
	intsct_pt = get_intsct_point(obj);
	to_light = normalize(vect_subt(rt->file_data->light.point, intsct_pt));
	// shade_factor = calc_shade_factor(obj, intsct_pt, to_light);
	// if (ft_inshadow(rt->file_data, intsct_pt, index, to_light)) // there is an object in the way
	// {
	// 	// printf("Under Shadow\n");
	// 	final_clr = blend(obj, rt->file_data->ambience.colour, shade_factor, rt->file_data->ambience.ratio);
	// }
	// else
	// {
	// 	// printf("No shadow\n");
	// 	final_clr = blend(obj, rt->file_data->light.colour, shade_factor, rt->file_data->light.ratio);
	// }
	final_clr = phong_calc(rt->file_data, index, intsct_pt, to_light);
	put_pxl(rt, ctr % rt->width, ctr / rt->width, (final_clr));
}

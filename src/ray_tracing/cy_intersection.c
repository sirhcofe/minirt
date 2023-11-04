/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:13:20 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/04 11:56:27 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	calc_intersection(t_coord ray, t_coord ori, t_cy *cylinder)
{
	double	lat_dist;
	double	endcap_dist;

	lat_intsct(&lat_dist, ray, ori, cylinder);
	if (isinf(lat_dist))
	{
		endcap_intsct(&endcap_dist, ray, ori, cylinder);
		return (endcap_dist);
	}
	else
		return (lat_dist);
}

void	to_cy_space(t_coord t_ori_vec[2], t_coord ray, t_coord ori, t_cy *cy)
{
	t_coord	offset;
	t_coord	z_axis;
	t_coord	rotation_axis;
	double	rotation_angle;

	set_coord(&offset, 0, 0, 0);
	set_coord(&z_axis, 0, 0, 1);
	t_ori_vec[0] = vect_add(ori, vect_subt(offset, cy->center));
	rotation_axis = normalize(cross_prod(cy->axis_vector, z_axis));
	if (is_zero_vector(rotation_axis))
		t_ori_vec[1] = ray;
	else
	{
		rotation_angle = acos(dot_prod(cy->axis_vector, z_axis));
		t_coord cy_new = rotation(&cy->axis_vector, rotation_angle, rotation_axis);
		t_ori_vec[0] = rotation(&t_ori_vec[0], rotation_angle, rotation_axis);
		t_ori_vec[1] = rotation(&ray, rotation_angle, rotation_axis);
	}
}

double	cy_intersection(t_coord ray_vec, t_coord origin, t_cy *cy)
{
	t_coord	trans_ori_vec[2];
	double	dist;

	to_cy_space(trans_ori_vec, ray_vec, origin, cy);
	dist = calc_intersection(trans_ori_vec[1], trans_ori_vec[0], cy);
	if (!isinf(dist))
		cy->intsct = vect_add(origin, vect_mult(ray_vec, dist));
	return (dist);
}

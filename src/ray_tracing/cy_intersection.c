/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:13:20 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/04 15:22:13 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// double	calc_intersection(t_coord ray, t_coord ori, t_cy *cylinder)
// {
// 	double	lat_dist;
// 	double	endcap_dist;

// 	lat_intsct(&lat_dist, ray, ori, cylinder);
// 	if (isinf(lat_dist))
// 	{
// 		endcap_intsct(&endcap_dist, ray, ori, cylinder);
// 		return (endcap_dist);
// 	}
// 	else
// 		return (lat_dist);
// }

/**
 * @brief Function calculates both situation of a cylinder intersection: on its
 * lateral surface, and on its end-caps. The smallest non-negative nor infinity
 * value will be the intersection distance.
 * @param ray The transformed ray vector in the common coordinate system.
 * @param ori The transformed ray origin in the common coordinate system.
 * @param cy The cylinder object.
 * @return Function returns the smallest non-negative distance between the
 * origin and the intersection on the cylinder object.
*/
double	calc_intersection(t_coord ray, t_coord ori, t_cy *cylinder)
{
	double	lat_dist;
	double	endcap_dist;

	lat_intsct(&lat_dist, ray, ori, cylinder);
	if (isinf(lat_dist))
		endcap_intsct(&endcap_dist, ray, ori, cylinder);
	if (isinf(lat_dist) && isinf(endcap_dist))
		return (INFINITY);
	else if (lat_dist < endcap_dist)
		return (lat_dist);
	else
		return (endcap_dist);
}

/**
 * @brief Function transforms ray vector and its origin to a common coordinate 
 * system where the cylinder is aligned with the z-axis, and its center is at
 * the origin.
 * @param t_ori_vec An array containing the translated ray vector and ray
 * origin.
 * @param ray The ray vector.
 * @param ori The ray origin.
 * @param cy The cylinder object.
 * @return Function does not return, while new transformed ray vector and origin
 * are stored in the array parsed as argument in the function. 
*/
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

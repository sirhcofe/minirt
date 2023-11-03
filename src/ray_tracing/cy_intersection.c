/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:13:20 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/03 22:14:59 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// double	handle_cy_found(double t[2])
// {
// 	// if (t[0] == INFINITY && t[1] == INFINITY)
// 	// 	return (INFINITY);
// 	// else if (t[0] != INFINITY && t[0] >= 0 && t[1] != INFINITY && t[1] >= 0)
// 	// {
// 	// 	if (t[0] < t[1])
// 	// 		return (t[0]);
// 	// 	else
// 	// 		return (t[1]);
// 	// }
// 	// else
// 	// {
// 	// 	if (t[0] != INFINITY && t[0] >= 0)
// 	// 		return (t[0]);
// 	// 	else if (t[1] != INFINITY && t[1] >= 0)
// 	// 		return (t[1]);
// 	// 	else
// 	// 		return (INFINITY);
// 	// }
// 	if (t[0] != INFINITY && t[0] >= 0 && t[1] != INFINITY && t[1] >= 0)
// 	{
// 		if (t[0] < t[1])
// 			return (t[0]);
// 		else
// 			return (t[1]);
// 	}
// 	else
// 	{
// 		if (t[0] != INFINITY && t[0] >= 0)
// 			return (t[0]);
// 		else if (t[1] != INFINITY && t[1] >= 0)
// 			return (t[1]);
// 	}
// }

double	handle_endcap(double z, t_coord ray, t_coord ori, t_cy *cy)
{
	double	v_comp[2];

	v_comp[0] = pow(ori.x, 2) + pow(ray.x, 2);
	v_comp[1] = pow(ori.y, 2) + pow(ray.y, 2);
	if (v_comp[0] + v_comp[1] <= pow(cy->height / 2, 2))
		return (z);
	else
		dprintf(2, "WTF\n");
}

double	compare_intsct_dist(double t[2])
{
	if (isinf(t[0]) && isinf(t[1]))
		return (INFINITY);
	else if (!isinf(t[0]) && t[0] >= 0 && !isinf(t[1]) && t[1] >= 0)
	{
		if (t[0] < t[1])
			return (t[0]);
		else
			return (t[1]);
	}
	else
	{
		if (!isinf(t[0]) && t[0] >= 0)
			return (t[0]);
		else if (!isinf(t[1]) && t[1] >= 0)
			return (t[1]);
		else
			return (INFINITY);
	}
}

double	handle_finite_length(double t[2], t_coord ray, t_coord ori, t_cy *cy)
{
	double	z[2];

	z[0] = ori.z + t[0] * ray.z;
	z[1] = ori.z + t[1] * ray.z;
	if (!(z[0] > -cy->height / 2 && z[0] < cy->height / 2))
		t[0] = INFINITY;
	if (!(z[1] > -cy->height / 2 && z[1] < cy->height / 2))
		t[1] = INFINITY;
	return (compare_intsct_dist(t));
}

void	endcap_intsct(double *dist, t_coord ray, t_coord ori, t_cy *cy)
{
	double	distance[2];
	double	t_top;
	double	t_bot;
	t_coord	intsct_top;
	t_coord	intsct_bot;

	t_top = ((cy->height / 2) - ori.z) / ray.z;
	intsct_top = vect_add(ori, vect_mult(ray, t_top));
	if (pow(intsct_top.x, 2) + pow(intsct_top.y, 2) <= pow(cy->radius, 2))
		distance[0] = t_top;
	else
		distance[0] = INFINITY;
	t_bot = ((-cy->height / 2) - ori.z) / ray.z;
	intsct_bot = vect_add(ori, vect_mult(ray, t_bot));
	if (pow(intsct_bot.x, 2) + pow(intsct_bot.y, 2) <= pow(cy->radius, 2))
		distance[1] = t_bot;
	else
		distance[1] = INFINITY;
	*dist = compare_intsct_dist(distance);
}

void	lat_intsct(double *dist, t_coord ray, t_coord ori, t_cy *cy)
{
	double	coeff[3];
	double	discriminant;
	double	t[2];
	double	z[2];

	coeff[0] = pow(ray.x, 2) + pow(ray.y, 2);
	coeff[1] = 2 * (ray.x * ori.x + ray.y * ori.y);
	coeff[2] = pow(ori.x, 2) + pow(ori.y, 2)
			- pow(cy->radius, 2);
	discriminant = pow(coeff[1], 2) - 4 * coeff[0] * coeff[2];
	if (discriminant >= 0)
	{
		t[0] = (-coeff[1] - sqrt(discriminant)) / (2 * coeff[0]);
		t[1] = (-coeff[1] + sqrt(discriminant)) / (2 * coeff[0]);
		// *dist = handle_finite_length(t, ray, ori, cy);
		z[0] = ori.z + t[0] * ray.z;
		z[1] = ori.z + t[1] * ray.z;
		if (!(z[0] > -cy->height / 2 && z[0] < cy->height / 2))
			t[0] = INFINITY;
		if (!(z[1] > -cy->height / 2 && z[1] < cy->height / 2))
			t[1] = INFINITY;
		*dist = compare_intsct_dist(t);
	}
	else
		*dist = INFINITY;
}

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

/**
 * @brief Function checks for each coordinate of a 3d vector, to determine if
 * the vector is empty ( <0, 0, 0> ). An incrementing integer is used to keep
 * track of every coordinate if its value is not empty. If the integer remained
 * zero, that means neither of the coordinate has a value, hence is a zero
 * vector.
 * @param vector The vector parsed for verification
 * @return Returns true if vector is zero; otherwise, returns false
*/
int	is_zero(t_coord vector)
{
	int	coord_not_zero;

	coord_not_zero = 0;
	if (vector.x > 0.00001 || vector.x < -0.00001)
		coord_not_zero++;
	if (vector.y > 0.00001 || vector.y < -0.00001)
		coord_not_zero++;
	if (vector.z > 0.00001 || vector.y < -0.00001)
		coord_not_zero++;
	if (coord_not_zero == 0)
		return (1);
	else
		return (0);
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
	if (is_zero(rotation_axis))
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
	return (dist);
}

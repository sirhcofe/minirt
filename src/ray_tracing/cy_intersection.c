/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:13:20 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/02 23:47:01 by chenlee          ###   ########.fr       */
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

int	approx(double value, double limit)
{
	double	difference;

	if (value <= -0.0001)
		value *= -1;
	difference = value - limit;
	if (difference > -0.0001 && difference < 0.0001)
		return (1);
	else
		return (0);
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
	if (t[0] != INFINITY && t[0] >= 0 && t[1] != INFINITY && t[1] >= 0)
	{
		if (t[0] < t[1])
			return (t[0]);
		else
			return (t[1]);
	}
	else
	{
		if (t[0] != INFINITY && t[0] >= 0)
			return (t[0]);
		else if (t[1] != INFINITY && t[1] >= 0)
			return (t[1]);
		else
			return (INFINITY);
	}
}

void	lat_intsct(double *dist, t_coord ray, t_coord ori, t_cy *cy)
{
	double	coeff[3];
	double	discriminant;
	double	t[2];

	coeff[0] = pow(ray.x, 2) + pow(ray.y, 2);
	coeff[1] = 2 * (ray.x * ori.x + ray.y * ori.y);
	coeff[2] = pow(ori.x, 2) + pow(ori.y, 2)
			- pow(cy->dia / 2, 2);
	discriminant = pow(coeff[1], 2) - 4 * coeff[0] * coeff[2];
	if (discriminant >= 0)
	{
		t[0] = (-coeff[1] - sqrt(discriminant)) / (2 * coeff[0]);
		t[1] = (-coeff[1] + sqrt(discriminant)) / (2 * coeff[0]);
		dprintf(2, "BEFORE: t[0]=%f && t[1]=%f\n", t[0], t[1]);
		dprintf(2, "BEOFRE: DIST=%f\n", *dist);
		*dist = handle_finite_length(t, ray, ori, cy);
		dprintf(2, "AFTERR: t[0]=%f && t[1]=%f\n", t[0], t[1]);
		dprintf(2, "AFTERR: DIST=%f\n", *dist);
	}
	else
		*dist = INFINITY;
}

double	calc_intersection(t_coord ray, t_coord ori, t_cy *cylinder)
{
	double	lat_dist;

	lat_intsct(&lat_dist, ray, ori, cylinder);
	dprintf(2, "IN CALC_INTER: %f\n", lat_dist);
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

t_coord	transform_to_cylinder_space(t_coord ray, t_coord origin, t_cy *cylinder, int mode)
{
	t_coord	offset;
	t_coord	z_axis;
	t_coord	perpendicular_vector;
	t_coord	rotation_axis;
	double	rotation_angle;

	set_coord(&offset, 0, 0, 0);
	set_coord(&z_axis, 0, 0, 1);
	perpendicular_vector = cross_prod(z_axis, cylinder->axis_vector);
	if (is_zero(perpendicular_vector))
	{
		if (mode == 1)
			return (ray);
		else if (mode == 2)
			return (vect_subt(origin, vect_subt(offset, cylinder->center)));
	}
	rotation_axis = normalize(perpendicular_vector);
	rotation_angle = acos(dot_prod(cylinder->axis_vector, z_axis));
	if (mode == 1)
		return (rotation(&ray, rotation_angle, rotation_axis));
	else if (mode == 2)
	{
		origin = vect_subt(origin, vect_subt(offset, cylinder->center));
		return (rotation(&origin, rotation_angle, rotation_axis));
	}
}

double	cy_intersection(t_coord ray_vec, t_coord origin, t_cy *cy)
{
	t_coord	trans_ray_vec;
	t_coord	trans_ray_ori;
	double	dist;
	int		ret;
	double	result;

	trans_ray_vec = transform_to_cylinder_space(ray_vec, origin, cy, 1);
	trans_ray_ori = transform_to_cylinder_space(ray_vec, origin, cy, 2);
	dist = calc_intersection(trans_ray_vec, trans_ray_ori, cy);
	dprintf(2, "DIST=%f\n", dist);
	return (dist);
}

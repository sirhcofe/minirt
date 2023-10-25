/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cy_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:13:20 by chenlee           #+#    #+#             */
/*   Updated: 2023/10/25 11:51:13 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	found_intersection(double intersection[2], t_coord t_ray_vec,
		t_coord t_ray_ori, t_cy *cylinder)
{
	double	coeff[3];
	double	discriminant;
	double	in_cylinder[2];

	coeff[0] = pow(t_ray_vec.x, 2) + pow(t_ray_vec.y, 2);
	coeff[1] = 2 * (t_ray_vec.x * t_ray_ori.x + t_ray_vec.y * t_ray_ori.y);
	coeff[2] = pow(t_ray_ori.x, 2) + pow(t_ray_ori.y, 2)
			- pow(cylinder->dia / 2, 2);
	discriminant = pow(coeff[1], 2) - 4 * coeff[0] * coeff[2];
	if (discriminant >= 0)
	{
		intersection[0] = (-coeff[1] - sqrt(discriminant)) / (2 * coeff[0]);
		intersection[1] = (-coeff[1] + sqrt(discriminant)) / (2 * coeff[0]);
		in_cylinder[0] = t_ray_ori.z + intersection[0] * t_ray_vec.z;
		in_cylinder[1] = t_ray_ori.z + intersection[1] * t_ray_vec.z;
		if (0 <= in_cylinder[0] <= cylinder->height
			|| 0 <= in_cylinder[1] <= cylinder->height)
			return (1);
	}
	return (0);
}

t_coord	transform_to_cylinder_space(t_coord ray, t_cy *cylinder, int mode)
{
	t_coord	rotation_axis;
	double	rotation_angle;
	t_coord z_axis;

	set_coord(&z_axis, 0, 0, 1);
	rotation_axis = normalize(cross_prod(cylinder->axis_vector, z_axis));
	rotation_angle = acos(dot_prod(cylinder->axis_vector, z_axis));
	if (mode == 1)
		return (rotation(&ray, rotation_angle));
	else if (mode == 2)
		return (vect_subt(rotation(&ray, rotation_angle), cylinder->center));
}


/**
 * @brief Function determines if an intersection on the cylinder occured on the
 * ray vector originating from camera origin. In order to ray trace a cylinder,
 * geometric transformations is required to scale, rotate, and translate the
 * primitives into desired locations. As a finite unit cylinder equation is a
 * quadratic equation of second order: x^2 + y^2 = 1, z_min < z < z_max. The
 * equation will give two values of t
 * @param dist The distance between the intersect and camera origin
 * @param ray_vec The ray vector originating from camera origin
 * @param ray_ori The coordinates of the caemra origin
 * @param cy The cylinder object
 * @return Function returns true if an intersection occured; otherwise, returns
 * false 
*/
int	get_cy_dist(double *dist, t_coord ray_vec, t_coord ray_ori, t_cy *cy)
{
	t_coord	trans_ray_vec;
	t_coord	trans_ray_ori;
	double	t[2];

	trans_ray_vec = transform_to_cylinder_space(ray_vec, cy, 1);
	trans_ray_ori = transform_to_cylinder_space(ray_ori, cy, 2);
	if (found_intersection(t, trans_ray_vec, trans_ray_ori, cy))
	{
		if (t[0] >= 0)
			*dist = t[0];
		else
			*dist = t[1];
		return 1;
	}
	else
		return 0;
}

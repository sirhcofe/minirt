/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cy_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:13:20 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/01 17:17:14 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	handle_cy_found(double t[2])
{
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
	}
}

int	approx(double number, double limit)
{
	double	difference;

	difference = number - limit;
	if (difference >= -0.0001 && difference <= 0.0001)
		return (1);
	else
		return (0);
}

double	ft_abs_diff(double num, double diff)
{
	if (num < -0.001)
		num *= -1;
	double	difference;
	difference = num - diff;
	if (difference > -0.001 && difference < 0.001)
		return (1);
	else
		return (0);
}

int	found_intersection(double *intsct, t_coord ray, t_coord ori, t_cy *cylinder)
{
	double	coeff[3];
	double	discriminant;
	double	z[2];
	int		intersection;

	coeff[0] = pow(ray.x, 2) + pow(ray.y, 2);
	coeff[1] = 2 * (ray.x * ori.x + ray.y * ori.y);
	coeff[2] = pow(ori.x, 2) + pow(ori.y, 2)
			- pow(cylinder->dia / 2, 2);
	// dprintf(2, "coeff 0=%f 1=%f 2=%f\n", coeff[0], coeff[1], coeff[2]);
	discriminant = pow(coeff[1], 2) - 4 * coeff[0] * coeff[2];
	// dprintf(2, "discriminant=%f\n", discriminant);
	if (discriminant >= 0)
	{
		intersection = 2;
		intsct[0] = (-coeff[1] - sqrt(discriminant)) / (2 * coeff[0]);
		intsct[1] = (-coeff[1] + sqrt(discriminant)) / (2 * coeff[0]);
		z[0] = ori.z + intsct[0] * ray.z;
		z[1] = ori.z + intsct[1] * ray.z;
		// dprintf(2, "======z=%f %f\n", z[0], z[1]);
		// if (-cylinder->height / 2 < z[0] < cylinder->height / 2
		// 	|| -cylinder->height / 2 < z[1] < cylinder->height / 2)
		// 	return (1);
		// dprintf(2, "z[0]=%f && z[1]=%f\n", z[0], z[1]);
		if (ft_abs_diff(z[0], cylinder->height / 2) || ft_abs_diff(z[1], cylinder->height / 2))
			dprintf(2, "CAPPEDDDDDD!!!!!!!\n");
		// if (!(z[0] > 0 && z[0] < cylinder->height))
		if (!(z[0] > -cylinder->height / 2 && z[0] < cylinder->height / 2))
		{
			intsct[0] = INFINITY;
			intersection--;
		}
		// if (!(z[1] > 0 && z[1] < cylinder->height))
		if (!(z[1] > -cylinder->height / 2 && z[1] < cylinder->height / 2))
		{
			intsct[1] = INFINITY;
			intersection--;
		}
		if (intersection > 0)
			return (1);
	}
	return (0);
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

t_coord	transform_to_cylinder_space(t_coord ray, t_cam camera, t_cy *cylinder, int mode)
{
	t_coord	offset;
	t_coord	z_axis;
	t_coord	perpendicular_vector;
	t_coord	rotation_axis;
	t_coord	transformed_ray;
	double	rotation_angle;

	set_coord(&offset, 0, 0, 0);
	set_coord(&z_axis, 0, 0, 1);
	// dprintf(2, "checking_cy_axis=%f %f %f\n", cylinder->axis_vector.x, cylinder->axis_vector.y, cylinder->axis_vector.z);
	perpendicular_vector = cross_prod(z_axis, cylinder->axis_vector);
	// dprintf(2, "perpendicular=%f %f %f\n", perpendicular_vector.x, perpendicular_vector.y, perpendicular_vector.z);
	if (is_zero(perpendicular_vector))
	{
		if (mode == 1)
			return (ray);
		else if (mode == 2)
			return (vect_subt(camera.point, vect_subt(offset, cylinder->center)));
	}
	rotation_axis = normalize(perpendicular_vector);
	// dprintf(2, "rot_axis=%f %f %f\n", rotation_axis.x, rotation_axis.y, rotation_axis.z);
	rotation_angle = acos(dot_prod(cylinder->axis_vector, z_axis));
	// dprintf(2, "rot_angle=%f\n", rotation_angle);
	// t_coord	rotated_cam = rotation(&camera.point, rotation_angle, rotation_axis);
	// dprintf(2, "rotated_CAM=%f %f %f\n", rotated_cam.x, rotated_cam.y, rotated_cam.z);
	if (mode == 1)
		return (rotation(&ray, rotation_angle, rotation_axis));
	else if (mode == 2)
	{
		camera.point = vect_subt(camera.point, vect_subt(offset, cylinder->center));
		return (rotation(&camera.point, rotation_angle, rotation_axis));
	}
}

int	get_cy_dist(double *dist, t_coord ray_vec, t_cam camera, t_cy *cy)
{
	t_coord	trans_ray_vec;
	t_coord	trans_ray_ori;
	double	t[2];
	int		ret;

	trans_ray_vec = transform_to_cylinder_space(ray_vec, camera, cy, 1);
	trans_ray_ori = transform_to_cylinder_space(ray_vec, camera, cy, 2);
	// dprintf(2, "translated_ray = %f %f %f\n", trans_ray_vec.x, trans_ray_vec.y, trans_ray_vec.z);
	// dprintf(2, "translated_ori = %f %f %f\n", trans_ray_ori.x, trans_ray_ori.y, trans_ray_ori.z);
	ret = found_intersection(t, trans_ray_vec, trans_ray_ori, cy);
	// dprintf(2, "\n");
	if (ret)
	{
		*dist = handle_cy_found(t);
		return 1;
	}
	else
		return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sp_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 08:15:57 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/03 22:16:44 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	handle_sp_found(double coeff[3], double discriminant)
{
	double	t[2];

	t[0] = (-coeff[1] + sqrt(discriminant)) / (2 * coeff[0]);
	t[1] = (-coeff[1] - sqrt(discriminant)) / (2 * coeff[0]);
	if (t[0] >= 0 && t[1] >= 0)
	{
		if (t[0] < t[1])
			return (t[0]);
		else
			return (t[1]);
	}
	else
	{
		if (t[0] >= 0)
			return (t[0]);
		else
			return (t[1]);
	}
}

int	get_sp_dist(double *dist, t_coord ray_vec, t_cam camera, t_sp *sp)
{
	double	coeff[3];
	double	discriminant;
	t_coord	sphere_offset;

	sphere_offset = vect_subt(camera.point, sp->center);
	coeff[0] = dot_prod(ray_vec, ray_vec);
	coeff[1] = 2 * dot_prod(ray_vec, sphere_offset);
	coeff[2] = dot_prod(sphere_offset, sphere_offset) - 1;
	discriminant = pow(coeff[1], 2) - 4 * coeff[0] * coeff[2];
	if (discriminant >= 0)
	{
		*dist = handle_sp_found(coeff, discriminant);
		return (1);
	}
	return (0);
}

/**
 * @brief Function determines if an intersection on the plane occured on the ray
 * vector. If the denominator (in which is the dot product of the plane's normal
 * vector and ray vector) is 0, then the ray is parallel to the plane, and there
 * is no intersection. If the intersetion t < 0, the plane is behind the camera
 * and there is no intersection; otherwise the intersection point is E + tD.
 * 
 * @param dist The distance between the intersect and camera origin
 * @param ray_vec The ray vector (D) originating from camera origin (E)
 * @param ray_ori The coordinates of camera origin
 * @param pl The plane object
*/

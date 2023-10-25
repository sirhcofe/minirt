/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sp_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 08:15:57 by chenlee           #+#    #+#             */
/*   Updated: 2023/10/25 11:52:28 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_sp_dist(double *dist, t_coord ray_vec, t_coord ray_ori, t_sp *sp)
{
	double	coeff[3];

	coeff[0] = pow(ray_vec.x, 2) + pow(ray_vec.y, 2) + pow(ray_vec.z, 2);
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

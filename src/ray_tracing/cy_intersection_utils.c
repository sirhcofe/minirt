/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_intersection_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:56:30 by chenlee           #+#    #+#             */
/*   Updated: 2024/01/17 22:53:23 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Function compares the 2 intersection distance value calculated from
 * solving the quadratic equation.
 * @param t The 2 intersection distance for comparison.
 * @return Function returns the smallest non-negative value.
*/
double	compare_cy_intsct(double t[2])
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

/**
 * @brief Function handles the z limit for the finite cylinder. If the z value
 * exceeds the cylinder height, that means there is no intersection.
 * @param t The 2 presumed intersection distance for an infinite cylinder.
 * @param ray The transformed ray vector.
 * @param ori The transformed ray origin.
 * @param cy The cylinder object that is transformed such that its z-axis aligns
 * with the global coordinates' z-axis.
*/
double	handle_finite_length(double t[2], t_coord ray, t_coord ori, t_cy *cy)
{
	double	z[2];

	z[0] = ori.z + t[0] * ray.z;
	z[1] = ori.z + t[1] * ray.z;
	if (!(z[0] > -cy->height / 2 && z[0] < cy->height / 2))
		t[0] = INFINITY;
	if (!(z[1] > -cy->height / 2 && z[1] < cy->height / 2))
		t[1] = INFINITY;
	return (compare_cy_intsct(t));
}

void	cy_endcap_intsct(double *dist, t_coord ray, t_coord ori, t_cy *cy)
{
	double	distance[2];
	double	t_top;
	double	t_bot;
	t_coord	intsct_top;
	t_coord	intsct_bot;

	t_top = ((cy->height / 2) - ori.z) / ray.z;
	intsct_top = vect_add(ori, vect_mult(ray, t_top));
	if (pow(intsct_top.x, 2) + pow(intsct_top.y, 2) <= pow(cy->radius, 2))
	{
		cy->intsct_type = 2;
		distance[0] = t_top;
	}
	else
		distance[0] = INFINITY;
	t_bot = ((-cy->height / 2) - ori.z) / ray.z;
	intsct_bot = vect_add(ori, vect_mult(ray, t_bot));
	if (pow(intsct_bot.x, 2) + pow(intsct_bot.y, 2) <= pow(cy->radius, 2))
	{
		cy->intsct_type = 3;
		distance[1] = t_bot;
	}
	else
		distance[1] = INFINITY;
	*dist = compare_cy_intsct(distance);
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
		z[0] = ori.z + t[0] * ray.z;
		z[1] = ori.z + t[1] * ray.z;
		if (!(z[0] > -cy->height / 2 && z[0] < cy->height / 2))
			t[0] = INFINITY;
		if (!(z[1] > -cy->height / 2 && z[1] < cy->height / 2))
			t[1] = INFINITY;
		*dist = compare_cy_intsct(t);
	}
	else
		*dist = INFINITY;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cy_intersection_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:56:30 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/04 11:56:38 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co_intersection_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 01:37:56 by chenlee           #+#    #+#             */
/*   Updated: 2024/01/22 14:21:41 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	co_endcap_intsct(double *dist, t_coord transltd[2], t_co *co)
{
	double	distance;
	t_coord	intsct;

	distance = ((co->height - transltd[ori].z) / transltd[vec].z);
	intsct = vect_add(transltd[ori], vect_mult(transltd[vec], distance));
	if (pow(intsct.x, 2) + pow(intsct.y, 2) <= pow(co->radius, 2))
	{
		co->intsct_type = 2;
		*dist = distance;
	}
	else
		*dist = INFINITY;
}

/**
 * @brief Function compares the 2 intersection distance value calculated from
 * solving the quadratic equation.
 * @param t The 2 intersection distance for comparison.
 * @return Function returns the smallest non-negative value.
*/
double	compare_co_intsct(double t[2])
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
 * Solves the quadratic equation to find potential intersection points with the
 * cone's surface
 * @param dist Pointer to store the distance of the closest valid intersection
 * @param coe Coefficients of the quadratic equation
 * @param transl Translated origin and direction vector of the ray
 * @param co The cone object
 * @return Function does not return
*/
void	solve_quadratic(double *dist, double coe[3], t_coord trnsl[2], t_co *co)
{
	double	discriminant;
	double	t[2];
	double	z[2];
	int		z_positive;

	z_positive = co->base_center.z > 0;
	discriminant = pow(coe[1], 2) - 4 * coe[0] * coe[2];
	if (discriminant >= 0)
	{
		t[0] = (-coe[1] - sqrt(discriminant)) / (2 * coe[0]);
		t[1] = (-coe[1] + sqrt(discriminant)) / (2 * coe[0]);
		z[0] = trnsl[ori].z + t[0] * trnsl[vec].z;
		z[1] = trnsl[ori].z + t[1] * trnsl[vec].z;
		if ((z_positive && (z[0] < 0 || z[0] > co->height))
			|| (!z_positive && (z[0] > 0 || z[0] < -co->height)))
			t[0] = INFINITY;
		if ((z_positive && (z[1] < 0 || z[1] > co->height))
			|| (!z_positive && (z[1] > 0 || z[1] < -co->height)))
			t[1] = INFINITY;
		*dist = compare_co_intsct(t);
	}
	else
		*dist = INFINITY;
}

void	conical_intsct(double *dist, t_coord transl[2], t_co *co)
{
	double	coef[3];
	double	r_div_h;

	r_div_h = pow(co->radius / co->height, 2);
	// coef[0] = pow(transl[vec].x, 2) + pow(transl[vec].y, 2)
	// 			- pow(transl[vec].z, 2) * r_div_h;
	// coef[1] = 2 * (transl[vec].x * transl[ori].x + transl[vec].y * transl[ori].y
	// 				- transl[vec].z * transl[ori].z * r_div_h);
	// coef[2] = pow(transl[ori].x, 2) + pow(transl[ori].y, 2)
	// 			- pow(transl[ori].z, 2) * r_div_h;
	coef[0] = pow(transl[vec].x, 2) + pow(transl[vec].y, 2)
		- pow(transl[vec].z, 2) * r_div_h;
	coef[1] = 2 * (transl[vec].x * transl[ori].x + transl[vec].y * transl[ori].y
			- transl[vec].z * transl[ori].z * r_div_h);
	coef[2] = pow(transl[ori].x, 2) + pow(transl[ori].y, 2)
		- pow(transl[ori].z, 2) * r_div_h;
	solve_quadratic(dist, coef, transl, co);
}

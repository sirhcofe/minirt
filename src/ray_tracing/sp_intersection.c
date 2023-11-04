/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:08:25 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/04 19:24:39 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Function compares the 2 values as a solution from solving the equation
 * of a sphere. Any non-negative value denote a valid intersection.
 * @param coeff The coefficient of the quadratic equation.
 * @param discriminant The value depending on the coefficients that allows
 * deducing some properties of the roots.
 * @return Function returns the smallest non-negative value, denoting the
 * closest intersection distance.
*/
double	handle_found_sp(double coeff[3], double discriminant)
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
		else if (t[1] >= 0)
			return (t[1]);
		else
			return (INFINITY);
	}
}

double	sp_intersection(t_coord ray_vec, t_coord origin, t_sp *sp)
{
	double	dist;
	double	coeff[3];
	double	discriminant;
	t_coord	offset;
	t_coord	transl_ori;

	set_coord(&offset, 0, 0, 0);
	transl_ori = vect_add(origin, vect_subt(offset, sp->center));
	coeff[0] = dot_prod(ray_vec, ray_vec);
	coeff[1] = 2 * dot_prod(ray_vec, transl_ori);
	coeff[2] = dot_prod(transl_ori, transl_ori) - pow(sp->dia / 2, 2);
	discriminant = pow(coeff[1], 2) - 4 * coeff[0] * coeff[2];
	if (discriminant >= 0)
		dist = handle_found_sp(coeff, discriminant);
	else
		dist = INFINITY;
	if (!isinf(dist))
		sp->intsct = vect_add(origin, vect_mult(ray_vec, dist));
	return (dist);
}

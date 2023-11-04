/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_intersection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:34:29 by jthor             #+#    #+#             */
/*   Updated: 2023/11/04 21:10:19 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	pl_intersection(t_coord ray_vector, t_coord ray_ori, t_pl *pl)
{
	double	dist;
	double	denom;
	double	numer;
	double	res;

	denom = dot_prod(ray_vector, pl->normal_vector);
	if (denom == 0)
		return (0);
	numer = dot_prod(pl->normal_vector, vect_subt(pl->point, ray_ori));
	res = numer / denom;
	if (res < 0)
		return (INFINITY);
	dist = res;
	pl->intsct = vect_add(ray_ori, vect_mult(ray_vector, dist));
	return (dist);
}

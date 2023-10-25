/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pl_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:34:29 by jthor             #+#    #+#             */
/*   Updated: 2023/10/25 12:34:33 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_pl_dist(double *dist, t_coord ray_vector, t_coord ray_ori, t_pl *plane)
{
	double	denom;
	double	numer;
	double	res;

	denom = dot_prod(ray_vector, plane->normal_vector);
	if (denom == 0)
		return (0);
	numer = dot_prod(plane->normal_vector, vect_subt(plane->point, ray_ori));
	res = numer / denom;
	if (res < 0)
		return (0);
	*dist = res;
	return (1);
}

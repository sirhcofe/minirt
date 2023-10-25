/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_algebra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 23:51:18 by chenlee           #+#    #+#             */
/*   Updated: 2023/10/25 11:48:13 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot_prod(t_coord a, t_coord b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_coord	cross_prod(t_coord a, t_coord b)
{
	t_coord	cross_product;

	cross_product.x = a.y * b.z - a.z * b.y;
	cross_product.y = a.z * b.x - a.x * b.z;
	cross_product.z = a.x * b.y - a.y * b.x;
	cross_product.w = 1;
	return (cross_product);
}

t_coord	normalize(t_coord a)
{
	t_coord	unit_vect;
	double	magnitude;

	magnitude = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	unit_vect.x = a.x / magnitude;
	unit_vect.y = a.y / magnitude;
	unit_vect.z = a.z / magnitude;
	return (unit_vect);
}

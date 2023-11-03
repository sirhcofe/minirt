/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:32:52 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/03 16:46:07 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	vect_mult(t_coord vector, double value)
{
	t_coord	ret;

	ret.x = vector.x * value;
	if (approx(ret.x, 0.0))
		ret.x = 0;
	ret.y = vector.y * value;
	if (approx(ret.y, 0.0))
		ret.y = 0;
	ret.z = vector.z * value;
	if (approx(ret.z, 0.0))
		ret.z = 0;
	ret.w = vector.w;
	return (ret);
}

t_coord	vect_add(t_coord a, t_coord b)
{
	t_coord	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_coord	vect_subt(t_coord a, t_coord b)
{
	t_coord	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

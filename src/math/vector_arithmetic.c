/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:32:52 by chenlee           #+#    #+#             */
/*   Updated: 2023/10/24 16:34:35 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	vect_mult(t_coord vector, double value)
{
	t_coord	ret;

	ret.x = vector.x * value;
	ret.y = vector.y * value;
	ret.z = vector.z * value;
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

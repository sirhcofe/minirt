/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geom_trans.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:52:10 by chenlee           #+#    #+#             */
/*   Updated: 2023/09/14 23:51:54 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	translation(t_coord *object)
{
	t_coord	transl_vector;

	transl_vector.x = 0 - object->x;
	transl_vector.y = 0 - object->y;
	transl_vector.z = 0 - object->z;
	transl_vector.w = object->w;
	return (transl_vector);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:27:01 by jthor             #+#    #+#             */
/*   Updated: 2023/11/07 23:27:03 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	*get_object(t_list *obj_lst, int index)
{
	int	iter;

	iter = -1;
	while (++iter < index)
		obj_lst = obj_lst->next;
	return ((t_object *)obj_lst->content);
}

t_coord	get_intsct_point(t_object *node)
{
	if (node->e_idx == sp)
		return (node->obj.sphere.intsct);
	else if (node->e_idx == pl)
		return (node->obj.plane.intsct);
	else
		return (node->obj.cylinder.intsct);
}

t_rgb	get_colour(t_object *obj)
{
	if (obj->e_idx == sp)
		return (obj->obj.sphere.colour);
	else if (obj->e_idx == pl)
		return (obj->obj.plane.colour);
	else
		return (obj->obj.cylinder.colour);
}

t_coord	deduce_normal(t_coord p2p, t_coord normal)
{
	if (dot_prod(p2p, normal) < 0)
		return(vect_mult(normal, -1));
	return (normal);
}

t_coord    get_cy_normal(t_cy obj, t_coord intsct)
{
    double    dist;
    t_coord    p2p_vector;
    t_coord    projection;
    t_coord    subtract_projection;

    p2p_vector = vect_subt(intsct, obj.center);
    projection = vect_mult(obj.axis_vector, dot_prod(projection, obj.axis_vector) / pow(vect_magnitude(intsct, obj.center), 2));
    subtract_projection = normalize(vect_subt(p2p_vector, projection));
    return (subtract_projection);
}
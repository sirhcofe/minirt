/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:27:01 by jthor             #+#    #+#             */
/*   Updated: 2024/01/19 15:02:32 by chenlee          ###   ########.fr       */
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
	else if (node->e_idx == cy)
		return (node->obj.cylinder.intsct);
	else
		return (node->obj.cone.intsct);
}

t_rgb	get_colour(t_object *obj)
{
	if (obj->e_idx == sp)
		return (obj->obj.sphere.colour);
	else if (obj->e_idx == pl)
		return (obj->obj.plane.colour);
	else if (obj->e_idx == cy)
		return (obj->obj.cylinder.colour);
	else
		return (obj->obj.cone.colour);
}

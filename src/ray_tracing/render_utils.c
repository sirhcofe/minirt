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

#include "minirt.h"

render_pixel(t_minirt *rt, t_coord *ray_vector, int index, size_t ctr)
{
	t_object	*obj;
	float		shade_factor;
	int			shadow_flag;
	int			final_colour;

	obj = get_object(rt->file_data->objects, index);
	shade_factor = calc_shading(obj, ray_vector);
	shadow_flag = is_blocked(obj, rt->file_data);
	final_colour = create_colour(0)
	if (shadow_flag == 0) // object is in light
}
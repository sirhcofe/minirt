#include "minirt.h"

void	render_pixel(t_minirt *rt, int index, size_t ctr)
{
	/* What I will need to calculate phong */
	t_object	*obj;
	t_coord		normal;
	t_coord		to_light;
	t_coord		to_viewer;
	t_coord		reflection;
	t_coord		intersect_point;
	double		dot_prod_res;

	/* Colour components */
	double		ambience_elem;
	double		diffuse_elem;
	double		secular_elem;

	/* The final colour results */
	t_rgb		light_contribution;
	t_rgb		final_colour;
	t_rgb		obj_col;
	double		final_pxl;

	/* Manual constant additions */
	double		secular_constant = 1;
	double		light_constant = 1;
	int			secular_sharpness = 20;
	double		light_rat = rt->file_data->light.ratio;
	double		object_rat = 1 - light_rat;

	/* Retrieving variables from ready made sources */
	obj = get_object(rt->file_data->objects, index);
	obj_col = get_colour(obj);
	intersect_point = get_intsct_point(obj);
	to_light = normalize(vect_subt(rt->file_data->light.point, intersect_point));
	to_viewer = normalize(vect_subt(rt->file_data->camera.point, intersect_point));

	normal = get_normal(obj, intersect_point, to_light);
	dot_prod_res = dot_prod(normal, to_light);

	/* Element retrieval */
	ambience_elem = rt->file_data->ambience.ratio;
	ambience_elem = 0;
	if (dot_prod_res < 0)
	{
		diffuse_elem = 0;
		secular_elem = 0;
	}
	else
	{
		reflection = vect_subt(vect_mult(normal, 2 * dot_prod(normal, to_light)), to_light);
		diffuse_elem = light_constant * dot_prod_res;
		secular_elem = secular_constant * pow(dot_prod(reflection, to_viewer), secular_sharpness);
	}

	/* Calculating light contribution */
	light_contribution.red = ambience_elem * rt->file_data->ambience.colour.red;
	light_contribution.red += diffuse_elem * rt->file_data->light.colour.red;
	light_contribution.red += secular_elem * rt->file_data->light.colour.red;

	light_contribution.blue = ambience_elem * rt->file_data->ambience.colour.blue;
	light_contribution.blue += diffuse_elem * rt->file_data->light.colour.blue;
	light_contribution.blue += secular_elem * rt->file_data->light.colour.blue;

	light_contribution.green = ambience_elem * rt->file_data->ambience.colour.green;
	light_contribution.green += diffuse_elem * rt->file_data->light.colour.green;
	light_contribution.green += secular_elem * rt->file_data->light.colour.green;

	/* Creating final blend */
	final_colour.red = obj_col.red * object_rat + light_contribution.red * light_rat;
	final_colour.green = obj_col.green * object_rat + light_contribution.green * light_rat;
	final_colour.blue = obj_col.blue * object_rat + light_contribution.blue * light_rat;

	/* Clamp */
	final_colour.red = (final_colour.red <= 0) ? 0 : final_colour.red;
	final_colour.red = (final_colour.red >= 255) ? 255 : final_colour.red;

	final_colour.green = (final_colour.green <= 0) ? 0 : final_colour.green;
	final_colour.green = (final_colour.green >= 255) ? 255 : final_colour.green;

	final_colour.blue = (final_colour.blue <= 0) ? 0 : final_colour.blue;
	final_colour.blue = (final_colour.blue >= 255) ? 255 : final_colour.blue;

	/* Final Blend */
	final_pxl = create_colour(0, final_colour.red, final_colour.green, final_colour.blue);
	put_pxl(rt, ctr % rt->width, ctr / rt->width, (final_pxl));
}
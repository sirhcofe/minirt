#include "minirt.h"

double	ft_max(double a, double b)
{
	if (approx(a, b))
		return a;
	if (a > b)
		return a;
	else
		return b;
}

void	render_pixel(t_minirt *rt, int index, size_t ctr)
{
	/* What I think I will need to calculate phong */
	t_object	*obj;
	t_coord		normal;
	t_coord		to_light;
	t_coord		to_viewer;
	t_coord		reflection;
	t_coord		intersect_point;
	t_rgb		obj_col;
	double		light_ratio = rt->file_data->light.ratio;

	/* Retrieving elements */
	obj = get_object(rt->file_data->objects, index);
	obj_col = get_colour(obj);
	intersect_point = get_intsct_point(obj);
	to_light = normalize(vect_subt(rt->file_data->light.point, intersect_point));
	to_viewer = normalize(vect_subt(rt->file_data->camera.point, intersect_point));
	normal = get_normal(obj, intersect_point, to_light);

	// ambient element
	t_amb	ambience;
	t_rgb	ambient;

	ambience = rt->file_data->ambience;
	ambient = ambience.colour;
	ambient.red = ambient.red * ambience.ratio;
	ambient.green = ambient.green * ambience.ratio;
	ambient.blue = ambient.blue * ambience.ratio;

	// diffuse lighting
	t_rgb	diffuse = rt->file_data->light.colour;
	double	diffuse_strength = ft_max(0.0, dot_prod(normal, to_light));

	diffuse.red = diffuse.red * diffuse_strength * light_ratio;
	diffuse.blue = diffuse.blue * diffuse_strength * light_ratio;
	diffuse.green = diffuse.green * diffuse_strength * light_ratio;

	// specular light
	reflection = vect_subt(vect_mult(normal, 2 * dot_prod(normal, to_light)), to_light);
	double	specular_strength = ft_max(0.0, dot_prod(reflection, to_viewer));
	specular_strength = pow(specular_strength, 20);
	t_rgb	specular = rt->file_data->light.colour;

	specular.red = specular.red * specular_strength;
	specular.green = specular.green * specular_strength;
	specular.blue = specular.blue * specular_strength;

	// lighting
	t_rgb	lighting;
	lighting.red = ambient.red + diffuse.red + specular.red;
	lighting.green = ambient.green + diffuse.green + specular.green;
	lighting.blue = ambient.blue + diffuse.blue + specular.blue;

	// colour to be printed
	t_rgb	final_colour;
	final_colour.red = obj_col.red * lighting.red * 255;
	final_colour.green = obj_col.green * lighting.green * 255;
	final_colour.blue = obj_col.blue * lighting.blue * 255;

	// clamp
	final_colour.red = (final_colour.red <= 0) ? 0 : final_colour.red;
	final_colour.red = (final_colour.red >= 255) ? 255 : final_colour.red;

	final_colour.green = (final_colour.green <= 0) ? 0 : final_colour.green;
	final_colour.green = (final_colour.green >= 255) ? 255 : final_colour.green;

	final_colour.blue = (final_colour.blue <= 0) ? 0 : final_colour.blue;
	final_colour.blue = (final_colour.blue >= 255) ? 255 : final_colour.blue;
	// printf("%f, %f, %f", final_colour.red, final_colour.green, final_colour.blue);

	// blend and place pixel
	double	pxl_col = create_colour(0, final_colour.red, final_colour.green, final_colour.blue);
	put_pxl(rt, ctr % rt->width, ctr / rt->width, pxl_col);
}
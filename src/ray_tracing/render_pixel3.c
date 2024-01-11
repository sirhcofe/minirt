#include "minirt.h"

// double	ft_max(double a, double b)
// {
// 	if (approx(a, b))
// 		return a;
// 	if (a > b)
// 		return a;
// 	else
// 		return b;
// }

// void	render_pixel(t_minirt *rt, int index, size_t ctr)
// {
// 	/* What I think I will need to calculate phong */
// 	t_object	*obj;
// 	t_coord		normal;
// 	t_coord		to_light;
// 	t_coord		to_viewer;
// 	t_coord		reflection;
// 	t_coord		intersect_point;
// 	t_rgb		obj_col;
// 	double		light_ratio = rt->file_data->light.ratio;

// 	/* Retrieving elements */
// 	obj = get_object(rt->file_data->objects, index);
	// obj_col = get_colour(obj);
// 	intersect_point = get_intsct_point(obj);
// 	to_light = normalize(vect_subt(rt->file_data->light.point, intersect_point));
// 	to_viewer = normalize(vect_subt(rt->file_data->camera.point, intersect_point));
// 	normal = get_normal(obj, intersect_point, to_light);

// 	// ambient element
// 	t_amb	ambience;
// 	t_rgb	ambient;

// 	ambience = rt->file_data->ambience;
// 	ambient = ambience.colour;
// 	ambient.red = ambient.red * ambience.ratio;
// 	ambient.green = ambient.green * ambience.ratio;
// 	ambient.blue = ambient.blue * ambience.ratio;

// 	// diffuse lighting
// 	t_rgb	diffuse = rt->file_data->light.colour;
// 	double	diffuse_strength = (ft_max(0.0, dot_prod(normal, to_light)));

// 	diffuse.red = diffuse.red * diffuse_strength * light_ratio;
// 	diffuse.blue = diffuse.blue * diffuse_strength * light_ratio;
// 	diffuse.green = diffuse.green * diffuse_strength * light_ratio;

// 	// specular light
// 	reflection = vect_subt(vect_mult(normal, 2 * dot_prod(normal, to_light)), to_light);
// 	double	specular_strength = ft_max(0.0, dot_prod(reflection, to_viewer));
// 	specular_strength = pow(specular_strength, 20);
// 	t_rgb	specular = rt->file_data->light.colour;

// 	specular.red = specular.red * specular_strength;
// 	specular.green = specular.green * specular_strength;
// 	specular.blue = specular.blue * specular_strength;

// 	// lighting
// 	t_rgb	lighting;
// 	lighting.red = ambient.red + diffuse.red + specular.red;
// 	lighting.green = ambient.green + diffuse.green + specular.green;
// 	lighting.blue = ambient.blue + diffuse.blue + specular.blue;

// 	// colour to be printed
// 	t_rgb	final_colour;
// 	final_colour.red = (obj_col.red * lighting.red) * 255;
// 	final_colour.green = (obj_col.green * lighting.green) * 255;
// 	final_colour.blue = (obj_col.blue * lighting.blue) * 255;

// 	// clamp
// 	final_colour.red = (final_colour.red <= 0) ? 0 : final_colour.red;
// 	final_colour.red = (final_colour.red >= 255) ? 255 : final_colour.red;

// 	final_colour.green = (final_colour.green <= 0) ? 0 : final_colour.green;
// 	final_colour.green = (final_colour.green >= 255) ? 255 : final_colour.green;

// 	final_colour.blue = (final_colour.blue <= 0) ? 0 : final_colour.blue;
// 	final_colour.blue = (final_colour.blue >= 255) ? 255 : final_colour.blue;
// 	// printf("%f, %f, %f", final_colour.red, final_colour.green, final_colour.blue);

// 	// blend and place pixel
// 	double	pxl_col = create_colour(0, final_colour.red, final_colour.green, final_colour.blue);
// 	put_pxl(rt, ctr % rt->width, ctr / rt->width, pxl_col);
// }

double	clamp(double color, double min, double max)
{
	if (color < min)
		return (min);
	else if (color > max)
		return (max);
	else
		return (color);
}

/**
 * Calculates the reflection vector given an incident vector and a normal vector
 * at the point of reflection.
 * @param i The normalized incident vector representing the incoming direction
 * of light or view vector.
 * @param n The normalized normal vector at the surface where the reflection
 * occurred.
 * @return The reflection vector calculated using the formula
 * R = I - 2 * (N · I) * N, where R is the reflection vector, I is the incident
 * vector, N is the normal vector, and (N · I) is the dot product of N and I.
*/
t_coord	reflect(t_coord i, t_coord n)
{
	t_coord	res;

	res.x = i.x - 2 * dot_prod(n, i) * n.x;
	res.y = i.y - 2 * dot_prod(n, i) * n.y;
	res.z = i.z - 2 * dot_prod(n, i) * n.z;
	return (res);
}

t_rgb	specular_component(t_minirt *rt, t_coord reflect_dir, t_coord to_viewer)
{
	double	spec;
	double	shininess;
	t_rgb	specular;

	shininess = 20;
	spec = pow(fmax(dot_prod(reflect_dir, to_viewer), 0.0), shininess);
	specular.red = spec * rt->file_data->light.colour.red
			* rt->file_data->light.ratio;
	specular.green = spec * rt->file_data->light.colour.green
			* rt->file_data->light.ratio;
	specular.blue = spec * rt->file_data->light.colour.blue
			* rt->file_data->light.ratio;
	return (specular);
}

t_rgb	diffuse_component(t_minirt *rt, t_coord normal, t_coord to_light, t_rgb obj_color)
{
	double	diff;
	t_rgb	diffuse;

	diff = fmax(dot_prod(normal, to_light), 0.0);
	diffuse.red = diff * obj_color.red * rt->file_data->light.colour.red
					* rt->file_data->light.ratio;
	diffuse.green = diff * obj_color.green * rt->file_data->light.colour.green
					* rt->file_data->light.ratio;
	diffuse.blue = diff * obj_color.blue * rt->file_data->light.colour.blue
					* rt->file_data->light.ratio;
	return (diffuse);
}

t_rgb	ambient_component(t_minirt *rt, t_object *obj, t_rgb obj_color)
{
	t_rgb	ambient_color;
	double	ambient_intensity;
	t_rgb	ambient;

	ambient_color = rt->file_data->ambience.colour;
	ambient_intensity = rt->file_data->ambience.ratio;
	ambient.red = obj_color.red * ambient_color.red * ambient_intensity;
	ambient.green = obj_color.green * ambient_color.green * ambient_intensity;
	ambient.blue = obj_color.blue * ambient_color.blue * ambient_intensity;
	return (ambient);
}

t_rgb	phong(t_minirt *rt, t_object *obj, t_rgb obj_color, t_coord intersect)
{
	
}

void	render_pixel(t_minirt *rt, int index, size_t ctr)
{
	t_object	*obj;
	t_rgb		obj_color;
	t_coord		intersect_pt;
	t_coord		to_light;
	t_coord		to_viewer;
	t_coord		normal;
	t_coord		reflect_dir;
	t_rgb		light_color;
	double		light_intensity;
	light_color = rt->file_data->light.colour;
	light_intensity = rt->file_data->light.ratio;
	int			shininess = 20; // 2-10 for matte sueface; 10-200 for moderate shiny; 1000++ for polished metal/mirror

	obj = get_object(rt->file_data->objects, index);
	obj_color = get_colour(obj);
	intersect_pt = get_intsct_point(obj);
	to_light = normalize(vect_subt(rt->file_data->light.point, intersect_pt));
	to_viewer = normalize(vect_subt(rt->file_data->camera.point, intersect_pt));
	normal = get_normal(obj, intersect_pt, to_light);
	reflect_dir = reflect(to_light, normal);

	// ambient component
	t_rgb	ambient;
	ambient = ambient_component(rt, obj, obj_color);
	

	// diffuse component
	t_rgb	diffuse;
	diffuse = diffuse_component(rt, normal, to_light, obj_color);

	// specular component
	t_rgb	specular;
	specular = specular_component(rt, reflect_dir, to_viewer);

	// combine component
	t_rgb	final;
	final = phong(rt, obj, obj_color, intersect_pt);

	final.red = ambient.red + diffuse.red + specular.red;
	final.green = ambient.green + diffuse.green + specular.green;
	final.blue = ambient.blue + diffuse.blue + specular.blue;

	// clamp
	final.red = clamp(final.red, 0.0, 1.0);
	final.green = clamp(final.green, 0.0, 1.0);
	final.blue = clamp(final.blue, 0.0, 1.0);

	// blend
	double	pxl_col = create_colour(0, final.red * 255, final.green * 255, final.blue * 255);
	put_pxl(rt, ctr % rt->width, ctr / rt->width, pxl_col);
}

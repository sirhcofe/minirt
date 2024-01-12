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

// 2-10 for matte sueface; 10-200 for moderate shiny; 1000++ for polished metal/mirror
t_rgb	specular_component(t_minirt *rt, t_coord reflect_dir, t_coord to_viewer)
{
	double	spec;
	double	shininess;
	t_rgb	specular;

	shininess = 10;
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

enum {
	to_light = 0,
	to_viewer = 1,
	normal = 2,
	reflect_dir = 3,
};

t_rgb	phong(t_minirt *rt, t_object *obj, t_rgb obj_color, t_coord *vectors)
{
	t_rgb	ambient;
	t_rgb	diffuse;
	t_rgb	specular;

	ambient = ambient_component(rt, obj, obj_color);
	diffuse = diffuse_component(rt, vectors[normal], vectors[to_light], obj_color);
	specular = specular_component(rt, vectors[reflect_dir], vectors[to_viewer]);
	return ((t_rgb){
		clamp(ambient.red + diffuse.red + specular.red, 0.0, 1.0),
		clamp(ambient.green + diffuse.green + specular.green, 0.0, 1.0),
		clamp(ambient.blue + diffuse.blue + specular.blue, 0.0, 1.0)
	});
}

int	ft_inshadow(t_data *f_data, t_coord intsct_pt, int index, t_coord to_light)
{
	t_list	*lst;
	int		curr;
	double	dist_val;

	curr = 0;
	lst = f_data->objects;
	while (lst)
	{
		if (index != curr)
		{
			dist_val = get_curr_dist(to_light, intsct_pt, lst->content);
			if (dist_val != INFINITY) // there is an object in the way
			{
				if (dist_val <= vect_magnitude(intsct_pt, f_data->light.point))
					return (1);
				// else the "obstructing" object is behind the light, so technically not in shadow
			}
		}
		curr++;
		lst = lst->next;
	}
	return (0);
}

void	calc_vect(t_minirt *rt, t_object *obj, t_coord *vectors, t_coord intsct)
{
	vectors[to_light] = normalize(vect_subt(rt->file_data->light.point,
			intsct));
	vectors[to_viewer] = normalize(vect_subt(rt->file_data->camera.point,
			intsct));
	vectors[normal] = get_normal(obj, intsct, vectors[to_light]);
	vectors[reflect_dir] = reflect(vect_mult(vectors[to_light], -1.0),
			vectors[normal]);
}

void	render_pixel(t_minirt *rt, int index, size_t ctr)
{
	t_object	*obj;
	t_rgb		obj_color;
	t_coord		intersect_pt;
	t_coord		vectors[4];
	t_rgb		final;

	obj = get_object(rt->file_data->objects, index);
	obj_color = get_colour(obj);
	intersect_pt = get_intsct_point(obj);
	calc_vect(rt, obj, vectors, intersect_pt);
	if (ft_inshadow(rt->file_data, intersect_pt, index, vectors[to_light])) // there is an object in the way
	{
		final.red = obj_color.red * rt->file_data->ambience.colour.red
				* rt->file_data->ambience.ratio;
		final.green = obj_color.green * rt->file_data->ambience.colour.green
				* rt->file_data->ambience.ratio;
		final.blue = obj_color.blue * rt->file_data->ambience.colour.blue
				* rt->file_data->ambience.ratio;
	}
	else
		final = phong(rt, obj, obj_color, vectors);

	// blend
	double	pxl_col = create_colour(0, final.red * 255, final.green * 255, final.blue * 255);
	put_pxl(rt, ctr % rt->width, ctr / rt->width, pxl_col);
}

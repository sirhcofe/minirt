/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:26:44 by jthor             #+#    #+#             */
/*   Updated: 2024/01/30 11:26:45 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 2-10 for matte sueface; 10-200 for moderate shiny;
// 1000+ for polished metal/mirror
t_rgb	specular_comp(t_minirt *rt, t_coord reflect_dir, t_coord to_viewer)
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

t_rgb	diffuse_comp(t_minirt *rt, t_coord norm, t_coord to_lgt, t_rgb obj_col)
{
	double	diff;
	t_rgb	diffuse;

	diff = fmax(dot_prod(norm, to_lgt), 0.0);
	diffuse.red = diff * obj_col.red * rt->file_data->light.colour.red
		* rt->file_data->light.ratio;
	diffuse.green = diff * obj_col.green * rt->file_data->light.colour.green
		* rt->file_data->light.ratio;
	diffuse.blue = diff * obj_col.blue * rt->file_data->light.colour.blue
		* rt->file_data->light.ratio;
	return (diffuse);
}

t_rgb	ambient_comp(t_minirt *rt, t_rgb obj_color)
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

t_rgb	phong(t_minirt *rt, t_rgb obj_color, t_coord *vectors)
{
	t_rgb	ambient;
	t_rgb	diffuse;
	t_rgb	specular;

	ambient = ambient_comp(rt, obj_color);
	diffuse = diffuse_comp(rt, vectors[normal], vectors[to_light], obj_color);
	specular = specular_comp(rt, vectors[reflect_dir], vectors[to_viewer]);
	return ((t_rgb){
		clamp(ambient.red + diffuse.red + specular.red, 0.0, 1.0) * 255,
		clamp(ambient.green + diffuse.green + specular.green, 0.0, 1.0) * 255,
		clamp(ambient.blue + diffuse.blue + specular.blue, 0.0, 1.0) * 255
	});
}

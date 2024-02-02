/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:52:43 by jthor             #+#    #+#             */
/*   Updated: 2024/01/30 17:52:45 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TRACING_H
# define RAY_TRACING_H

# include "objects.h"

/***************************** co_intersection.c ******************************/

/**
 * @brief Function calculates the intersection of a ray with a cone.
 * @param ray_vec Direction vector of the ray
 * @param origin Origin of the ray
 * @param co The cone object
 * @return The distance to the closest intersection point. Returns INFINITY if
 * there is no intersection
*/
double	co_intersection(t_coord ray_vec, t_coord origin, t_co *co);

/*************************** co_intersection_utils.c **************************/

/**
 * @brief Function calculates the intersection of a ray with the conical
 * surface of a cone.
 * @param dist Pointer to store the distance from the ray origin to the
 * intersection point.
 * @param transl Translated origin and direction vector of the ray
 * @param co The cone object
 * @return Function does not return
*/
void	conical_intsct(double *dist, t_coord transl[2], t_co *co);
/**
 * @brief Function calculates the intersection of a ray with the endcap of a
 * cone.
 * @param dist Pointer to store the distance from the ray origin to the
 * intersection point.
 * @param transl Translated origin and direction vector of the ray
 * @param co The cone object
 * @return Function does not return
*/
void	co_endcap_intsct(double *dist, t_coord transltd[2], t_co *co);

/***************************** cy_intersection.c ******************************/

/**
 * @brief Function determines if an intersection on the cylinder occured on the
 * ray vector originating from origin. In order to ray trace a cylinder,
 * geometric transformations is required to rotate and translate the primitives
 * into desired locations. As a finite closed cylinder, we consider:
 * 1. Intersection on its lateral surface: x^2 + y^2 = r^2, z_min <= z <= z_max.
 * 2. Intersection on its end caps: x^2 + y^2 <= r^2, z = z_min || z = z_max.
 * In both scenratio, the equations will give four values of t, and the smallest
 * non-negative value will be the intersection distance, while the intersection
 * point can be defined by E + tD
 * @param ray_vec The ray vector (D) originating from the origin (E)
 * @param ray_ori The coordinates of the origin
 * @param cy The cylinder object
 * @return Function returns the smallest non-negative value as the distance of
 * intersection, while storing the intersection point in the object itself.
*/
double	cy_intersection(t_coord ray_vec, t_coord origin, t_cy *cy);

/*************************** cy_intersection_utils.c **************************/

/**
 * @brief Function calculates the intersection of a ray with the end caps of a
 * cylinder.
 * @param dist Pointer to a double to store the computed intersection distance.
 * @param ray The translated ray direction vector.
 * @param ori The translated ray origin coordinates.
 * @param cy The cylinder object.
 * @return Function does not return.
*/
void	cy_endcap_intsct(double *dist, t_coord ray, t_coord ori, t_cy *cy);

/**
 * @brief Function determines the intersection of a ray with the lateral surface
 * of a cylinder.
 * @param dist Pointer to a double to store the computed intersection distance.
 * @param ray The translated ray direction vector.
 * @param ori The translated ray origin coordinates.
 * @param cy The cylinder object.
 * @return Function does not return.
*/
void	lat_intsct(double *dist, t_coord ray, t_coord ori, t_cy *cy);

/****************************** sp_intersection.c *****************************/

/**
 * @brief Function determines if an intersection on the sphere occured on the
 * ray vector. If the discriminant is non-negative, that means that there is
 * intersection between the ray and the sphere. Solving the quadratic equation
 * will return either 1 or 2 real values for t, and the smallest, non-negative
 * value will be the intersection point.
 * @param ray_vec The ray vector originating from origin
 * @param origin The coordinates of the origin
 * @param sp The sphere object
 * @return Function returns the smallest non-negative value as the distance of
 * intersection, while storing the intersection point in the object itself.
*/
double	sp_intersection(t_coord ray_vec, t_coord origin, t_sp *sp);

/**************************** pl_intersection.c ****************************/

/**
 * @brief Determines if the ray_vector intersects with the plane and calculates
 * the distance between them if there is an intersection
 * @param ray_vector The directional vector from the viewer
 * @param ray_ori The coordinates of the camera
 * @param pl The struct holding the data of the plane object
 * @return The distance between the camera and the point of intersection
*/
double	pl_intersection(t_coord ray_vector, t_coord ray_ori, t_pl *pl);

/****************************** render_pixel.c ******************************/

/**
 * @brief Renders the pixel by determining the colour, shade and shadow
 * factors.
 * @param rt Pointer to the t_minirt struct for mlx and object data
 * @param index The index of the object whose surface we are trying to colour.
 * @param ctr The current pixel we are looking at, before breaking it down to
 * (x, y) values.
 * @param ray_ori The ray from the camera to the point on the object.
 * @return Function returns nothing.
 */
void	render_pixel(t_minirt *rt, int index, size_t ctr, t_coord ray_ori);
/**
 * @brief Determines if that particular point is blocked from the light source.
 * @param f_dat Pointer to the t_data struct.
 * @param intsct_pt The point whose shadow factor is to be determined.
 * @param idx The index of the curremt object in the linked list.
 * @param to_lgt The vector from the intersection point to the light source.
 * @return Boolean int that tells us if the particular point is under the
 * shadow or not.
 * @retval 0 - The object is not in shadow.
 * @retval 1 - The object is in shadow.
 */
int		ft_inshadow(t_data *f_dat, t_coord intsct_pt, int idx, t_coord *vects);

/****************************** render_utils.c ******************************/

/**
 * @brief Takes the intersect point between the object and incident ray.
 * @return The coordinates of the intersection point.
 * @param node The pointer to the t_object struct.
*/
t_coord	get_intsct_point(t_object *node);
/**
 * @brief Takes the RGB component of the object.
 * @return The RGB component.
 * @param obj The pointer to the t_object struct.
*/
t_rgb	get_colour(t_object *obj);
/**
 * @brief Determines the normal to the surface of the cylinder at the
 * intersection point.
 * @param obj The cylinder object.
 * @param intsct The intersection point on the surface of the cylinder object.
 * @param axis_vect The cylinder's axis, as a normalised vector.
 * @return The normal to the surface of the cylinder that passes through the
 * intersection point.
 */
t_coord	get_cy_normal(t_cy obj, t_coord intsct, t_coord axis_vect);
/**
 * @brief Retrieves the normal vector from the surface of the passed object.
 * @param obj Pointer to the object, determines what kind of object we are
 * looking at here.
 * @param intsct The intersection point between the camera ray and the object.
 * @param to_light The normalised vector connecting the intersection point on
 * the object to the light source.
 * @returns The normalised vector representing the surface normal.
 */
t_coord	get_normal(t_object *obj, t_coord intsct, t_coord to_light);

/********************************* phong.c *********************************/

/**
 * @brief Calculates the colour of a pixel using phong lighting.
 * @param rt Pointer to the t_minirt struct to get light data.
 * @param obj Pointer to the object, predominantly used for colour.
 * @param obj
*/
t_rgb	phong(t_minirt *rt, t_rgb obj_color, t_coord *vectors);

#endif

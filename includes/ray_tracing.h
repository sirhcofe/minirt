#ifndef RAY_TRACING_H
#define RAY_TRACING_H

#include "objects.h"

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
void	endcap_intsct(double *dist, t_coord ray, t_coord ori, t_cy *cy);

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

/******************************* pl_intersection.c *******************************/

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
 * @return Function returns nothing.
 */
void	render_pixel(t_minirt *rt, int index, size_t ctr);
/**
 * @brief Blends the colour from the object and the appropriate source, and
 * considers the shade factor of the point.
 * @param obj Pointer to the object whose surface we are trying to colour.
 * @param src The RGB elements of etither the light source or ambient lighting.
 * @param shade_factor The factor that determines how dark the pixel should be.
 * @return The final colour that is to be rendered on the pixel.
 */
int	blend(t_object *obj, t_rgb src, double shade_factor);
/**
 * @brief Determines if that particular point is blocked from the light source.
 * @param f_data Pointer to the t_data struct.
 * @param intsct_pt The point whose shadow factor is to be determined.
 * @param index The index of the curremt object in the linked list.
 * @param to_light The vector from the intersection point to the light source.
 * @return Boolean int that tells us if the particular point is under the
 * shadow or not.
 * @retval 0 - The object is not in shadow.
 * @retval 1 - The object is in shadow.
 */
int	ft_inshadow(t_data *f_data, t_coord intsct_pt, int index, t_coord to_light);

#endif
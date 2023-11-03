#ifndef RAY_TRACING_H
#define RAY_TRACING_H

#include "objects.h"

/******************************* get_cy_dist.c *******************************/

/**
 * @brief Function determines if an intersection on the cylinder occured on the
 * ray vector originating from camera origin. In order to ray trace a cylinder,
 * geometric transformations is required to scale, rotate, and translate the
 * primitives into desired locations. As a finite unit cylinder equation is a
 * quadratic equation of second order: x^2 + y^2 = 1, z_min <= z <= z_max. The
 * equation will give two values of t, and the smallest non-negative value will
 * be the intersection distance, while the intersection point can be defined by
 * E + tD
 * @param ray_vec The ray vector (D) originating from camera origin (E)
 * @param ray_ori The coordinates of the caemra origin
 * @param cy The cylinder object
 * @return Function returns true if an intersection occured; otherwise, returns
 * false 
*/
double	get_cy_dist(t_coord ray_vec, t_coord ray_ori, t_cy *cy);

/******************************* get_sp_dist.c *******************************/

/**
 * @brief Function determines if an intersection on the sphere occured on the
 * ray vector. If the discriminant is non-negative, that means that there is
 * intersection between the ray and the sphere. Solving the quadratic equation
 * will return either 1 or 2 real values for t, and the smallest, non-negative
 * value will be the intersection point.
 * @param ray_vec The ray vector originating from camera origin
 * @param ray_ori The coordinates of camera origin
 * @param sp The sphere object
*/
double	get_sp_dist(t_coord ray_vec, t_coord ray_ori, t_sp *sp);

/******************************* get_pl_dist.c *******************************/

/**
 * @brief Determines if the ray_vector intersects with the plane and calculates
 * the distance between them if there is an intersection
 * @param ray_vector The directional vector from the viewer
 * @param ray_ori The coordinates of the camera
 * @param plane The struct holding the data of the plane object
 * @return The distance between the camera and the point of intersection
*/
double	get_pl_dist(t_coord ray_vector, t_coord ray_ori, t_pl *plane);

#endif
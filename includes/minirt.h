#ifndef MINIRT_H
#define MINIRT_H

#define BUFFER_SIZE 50
#define MAX_INT 2147483647

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include "libft.h"
#include "mlx.h"
#include "objects.h"
#include "driver.h"
#include "init.h"
#include "mathematics.h"
#include "mem_free.h"
#include "parse.h"
#include "ray_tracing.h"
#include "utils.h"

/******************************* -.- Shapes -.- *******************************/

/* plane_intersection.c */

/**
 * @brief Determines if the ray_vector intersects with the plane and calculates
 * the distance between them if there is an intersection
 * @param dist Pointer to a double that stores the distance between the camera
 * and the plane, if any
 * @param ray_vector The directional vector from the viewer
 * @param ray_ori The coordinates of the camera
 * @param plane The struct holding the data of the plane object
 * @return Integer boolean that shows the ray_vector intersects with the plane
 * @retval 1 if there is an intersection
 * @retval 0 if there is no intersection
*/
int	get_pl_dist(double *dist, t_coord ray_vector, t_coord ray_ori, t_pl *plane);

void	set_controls(t_minirt *rt);

#endif
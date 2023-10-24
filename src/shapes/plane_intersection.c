#include "minirt.h"

/**
 * WARNING: There is currently no difference between the two scenarios;
 * 1. The object does not intersect with the ray
 * 2. The object is right in front of the camera (distance is 0)
 * 
 * BOTH RETURNS 0
*/
double	get_pl_dist(t_coord *ray_vector, t_pl *plane, t_cam camera)
{
	double	denom;
	double	numer;
	t_coord	*temp1;
	t_coord	temp2;

	temp1 = &(plane->normal_vector);
	denom = dot_prod(ray_vector, temp1);
	if (denom == 0) // no intersection point
		return (0);
	temp2 = vect_subt(plane->point, camera.point);
	numer = dot_prod(temp1, &temp2);
	numer = numer / denom;
	if (numer < 0) // Intersection is behind camera
		return (0);
	else
		return (numer);
}
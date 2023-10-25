#include "minirt.h"

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
		return (-1);
	else
		return (numer);
}

int	get_pl_dist(double *dist, t_coord ray_vector, t_coord ray_ori, t_pl *plane)
{
	double	denom;
	double	numer;
	double	res;

	denom = dot_prod(ray_vector, plane->normal_vector);
	if (denom == 0) // no intersect
		return (0);
	numer = dot_prod(plane->normal_vector, vect_subt(plane->point, ray_ori));
	res = numer / denom;
	if (res < 0) // Intersection is behind camera
		return (0);
	if (res < *dist) // check if the current object is closer than the 
}
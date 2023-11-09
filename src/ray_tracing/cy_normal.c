#include "minirt.h"

t_coord	get_cy_normal(t_cy obj, t_coord intsct)
{
	double	dist;
	t_coord	cross_res;
	t_coord	p2p_vector;

	p2p_vector = vect_subt(obj.center, intsct);
	cross_res = cross_prod(obj.axis_vector, p2p_vector);
	dist = vect_magnitude(cross_res, (t_coord){0, 0, 0, 1});
	if (approx(dist, obj.radius) == 1) // The intsct point is on the curved surface
		return ();
	else
		return ();
}
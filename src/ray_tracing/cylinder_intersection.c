/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:13:20 by chenlee           #+#    #+#             */
/*   Updated: 2023/09/18 00:33:05 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	transform_to_cylinder_space(t_coord ray, int mode)
{
	if (mode == 1)
	{
		
	}
}

double	cylinder_intersection(t_coord ray, t_coord ray_origin, t_cy *cylinder)
{
	t_coord	trans_ray;
	t_coord	trans_ray_ori;

	trans_ray = transform_to_cylinder_space(ray, 1);
}

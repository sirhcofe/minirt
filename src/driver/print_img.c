/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:01:41 by jthor             #+#    #+#             */
/*   Updated: 2023/09/18 00:01:44 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// WIP : Figure out the image height and width

void	print_image(t_minirt *rt)
{
	t_coord	*ray_vector;
	size_t	ctr;
	int		index;

	if (rt->file_data->num_sp + rt->file_data->num_pl + rt->file_data->num_cy)
	{
		ctr = -1;
		while (++ctr < (rt->height * rt->width))
		{
			ray_vector = get_ray_vector(rt, ctr);
			index = get_touchy(rt, ray_vector);
			if (index == -1)
				void_pixel(rt, ctr);
			else
				colour_pixel(rt, ray_vector, index, ctr);
			free(ray_vector);
		}
	}
	else
		empty_protocol(rt);
}

void	empty_protocol(t_minirt *rt)
{
	size_t	ctr;
	int		colour;

	ctr = -1;
	while (++ctr < (rt->height * rt->width))
		void_pixel(rt, ctr);
}

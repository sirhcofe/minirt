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
	t_list	*objects;
	t_coord	*ray_vector;
	size_t	ctr;
	int		index;

	objects = combine_lists(rt);
	if (!objects)
	{
		empty_protocol(rt);
		return ;
	}
	ctr = -1;
	while (++ctr < (rt->height * rt->width))
	{
		ray_vector = get_ray_vector(rt->file_data->camera, ctr);
		index = get_touchy(rt, ray_vector, objects);
		if (index == -1)
			void_pixel(rt, ctr);
		else
			colour_pixel(rt, ray_vector, index, ctr);
		free(ray_vector);
	}
}

void	void_pixel(t_minirt *rt, int idx)
{
	int	colour;

	colour = create_colour(rt->file_data->ambience);
	put_pxl(rt, idx % rt->height, idx / rt->height, colour);
}

void	empty_protocol(t_minirt *rt)
{
	size_t	ctr;
	int		colour;

	ctr = -1;
	while (++ctr < (rt->height * rt->width))
		void_pixel(rt, ctr);
}

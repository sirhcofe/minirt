/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:40:05 by jthor             #+#    #+#             */
/*   Updated: 2023/09/18 00:40:07 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_pxl(t_minirt *rt, int x, int y, int colour)
{
	char	*dst;

	dst = rt->addr + (y * rt->line_len + x * (rt->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

void	void_pixel(t_minirt *rt, int idx)
{
	int	colour;

	colour = create_colour(rt->file_data->ambience);
	put_pxl(rt, idx % rt->height, idx / rt->height, colour);
}

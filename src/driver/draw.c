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

int	create_colour(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	put_pxl(t_minirt *rt, int x, int y, int colour)
{
	char	*dst;

	dst = rt->addr + (y * rt->line_len + x * (rt->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

void	void_pixel(t_minirt *rt, t_rgb amb_col, int idx)
{
	int	colour;

	// uncomment for render_pixel3
	// colour = create_colour(0, amb_col.red * 255, amb_col.green * 255, amb_col.blue * 255);
	colour = create_colour(0, amb_col.red, amb_col.green, amb_col.blue);
	put_pxl(rt, idx % rt->width, idx / rt->width, colour);
}

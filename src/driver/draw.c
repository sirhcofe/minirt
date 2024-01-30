/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:40:05 by jthor             #+#    #+#             */
/*   Updated: 2024/01/10 16:52:55 by chenlee          ###   ########.fr       */
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

void	void_pixel(t_minirt *rt, int idx)
{
	int	colour;

	put_pxl(rt, idx % rt->width, idx / rt->width, 0);
}

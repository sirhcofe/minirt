/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_window_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:16:57 by chenlee           #+#    #+#             */
/*   Updated: 2023/09/02 17:29:00 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_resolution(t_minirt *rt)
{
	int		fd;
	char	*resolution;
	char	**width_height;

	fd = open("resolution", O_RDONLY);
	resolution = get_next_line(fd);
	width_height = ft_split(resolution, 'x');
	rt->window_w = ft_atoi(width_height[0]) * 0.9;
	rt->window_h = ft_atoi(width_height[1]) * 0.9;
	free_split(width_height);
	free(resolution);
}

void	init_mlx_window(t_minirt *rt)
{
	rt->mlx = mlx_init();
	get_resolution(rt);
	rt->mlx_win = mlx_new_window(rt->mlx, rt->window_w, rt->window_h, "minirt");
	rt->img = mlx_new_image(rt->mlx, rt->window_w, rt->window_h);
	rt->addr = mlx_get_data_addr(rt->img, &(rt->bits_per_pixel),
			&(rt->line_len), &(rt->endian));
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
	mlx_loop(rt->mlx);
}

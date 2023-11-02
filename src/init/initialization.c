/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:16:57 by chenlee           #+#    #+#             */
/*   Updated: 2023/11/03 00:22:02 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_minirt	*init_mlx_window(void)
{
	t_minirt	*rt;

	rt = malloc(sizeof(t_minirt));
	rt->mlx = mlx_init();
	// rt->width = 40;
	// rt->height = 20;
	rt->width = 1280;
	rt->height = 720;
	rt->mlx_win = mlx_new_window(rt->mlx, rt->width, rt->height, "minirt");
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	rt->addr = mlx_get_data_addr(rt->img, &(rt->bits_per_pixel),
			&(rt->line_len), &(rt->endian));
	rt->file_data = malloc(sizeof(t_data));
	return (rt);
}

void	init_data_struct(t_data **f_data)
{
	*(f_data) = malloc(sizeof(t_data));
	(*f_data)->ambience.flag = 0;
	(*f_data)->camera.flag = 0;
	(*f_data)->light.flag = 0;
}

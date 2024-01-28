/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:16:57 by chenlee           #+#    #+#             */
/*   Updated: 2024/01/14 01:05:26 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_minirt	*init_mlx_window(void)
{
	t_minirt	*rt;

	rt = malloc(sizeof(t_minirt));
	rt->mlx = mlx_init();
	rt->width = 640;
	rt->height = 480;
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
	(*f_data)->num_sp = 0;
	(*f_data)->num_pl = 0;
	(*f_data)->num_cy = 0;
	(*f_data)->num_co = 0;
	(*f_data)->objects = NULL;
	(*f_data)->ambience.flag = 0;
	(*f_data)->camera.flag = 0;
	(*f_data)->light.flag = 0;
}

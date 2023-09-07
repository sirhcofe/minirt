/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 16:16:57 by chenlee           #+#    #+#             */
/*   Updated: 2023/09/07 16:29:59 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_minirt	*init_mlx_window(void)
{
	t_minirt	*rt;

	rt = malloc(sizeof(t_minirt));
	rt->mlx = mlx_init();
	rt->mlx_win = mlx_new_window(rt->mlx, 1280, 720, "minirt");
	rt->img = mlx_new_image(rt->mlx, 1280, 720);
	rt->addr = mlx_get_data_addr(rt->img, &(rt->bits_per_pixel),
			&(rt->line_len), &(rt->endian));
	rt->file_data = malloc(sizeof(t_data));
	return (rt);
}
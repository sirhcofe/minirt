/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 00:06:02 by chenlee           #+#    #+#             */
/*   Updated: 2024/01/30 18:06:07 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <unistd.h>

int	key_press(int key, t_minirt *rt)
{
	if (key == 53 || key == 65307)
	{
		free_data(rt);
		exit(0);
	}
	return (0);
}

int handle_resize(int width, int height, void *param)
{
	t_minirt	*rt;

	rt = (t_minirt *)(param);
	printf("width:%d, height=%d\n", rt->width, rt->height);
	// mlx_destroy_window(rt->mlx, rt->mlx_win);
    // Update image buffer size and redraw graphics
    // ...
    // Render the updated image to the window
	// rt->mlx_win = mlx_new_window(rt->mlx, width, height, "minirt");
	// rt->img = mlx_new_image(rt->mlx, width, height);
	// rt->addr = mlx_get_data_addr(rt->img, &(rt->bits_per_pixel),
	// 		&(rt->line_len), &(rt->endian));
	// mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
	// mlx_loop(rt->mlx);
	return (0);
}

int	close_program(t_minirt *rt)
{
	free_data(rt);
	exit(0);
}

int	xd(t_minirt *rt)
{
	printf("WHAT\n");
}

void	set_controls(t_minirt *rt)
{
	mlx_key_hook(rt->mlx_win, key_press, rt);
	mlx_hook(rt->mlx_win, 22, 1L<<17, handle_resize, &rt);
	mlx_hook(rt->mlx_win, 17, 0, close_program, rt);
}

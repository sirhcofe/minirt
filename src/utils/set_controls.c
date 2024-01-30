/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 00:06:02 by chenlee           #+#    #+#             */
/*   Updated: 2024/01/30 19:29:42 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_press(int key, t_minirt *rt)
{
	printf("key %d\n", key);
	if ((!IS_LINUX && key == 53) || (IS_LINUX && key == 65307))
	{
		free_data(rt);
		exit(0);
	}
	return (0);
}

int	close_program(t_minirt *rt)
{
	free_data(rt);
	exit(0);
}

void	set_controls(t_minirt *rt)
{
	mlx_key_hook(rt->mlx_win, key_press, rt);
	mlx_hook(rt->mlx_win, 17, 0, close_program, rt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 00:06:02 by chenlee           #+#    #+#             */
/*   Updated: 2023/09/06 00:53:11 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "stdio.h"

typedef struct	s_mem
{
	t_data		*f_data;
	t_minirt	*rt;
}	t_mem;

void	key_press(int key, t_mem *mem)
{
	if (key == 65307)
	{
		// free_data(mem->f_data, mem->rt);
		exit(0);
	}
	return ;
}

int	close_program(t_mem *mem)
{
	exit(0);
}

void	set_controls(t_data *f_data, t_minirt *rt)
{
	mlx_key_hook(rt->mlx_win, key_press, rt);
	mlx_hook(rt->mlx_win, 17, 0, close_program, rt);
}
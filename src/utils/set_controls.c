/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_controls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 00:06:02 by chenlee           #+#    #+#             */
/*   Updated: 2024/02/03 17:58:30 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_img_refresh(t_minirt *rt)
{
	mlx_destroy_image(rt->mlx, rt->img);
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	rt->addr = mlx_get_data_addr(rt->img, &(rt->bits_per_pixel),
			&(rt->line_len), &rt->endian);
}

void	switch_target(t_minirt *rt, int keycode)
{
	if (rt->editor.flag == NOT_EDIT)
	{
		printf("\033[31mEditor mode not enabled!\033[0m\n");
		return ;
	}
	else if (keycode == NUM_1)
	{
		rt->editor.flag = CAM_EDIT;
		set_editing_type(rt, 0);
	}
	else if (keycode == NUM_2)
	{
		rt->editor.flag = LIGHT_EDIT;
		set_editing_type(rt, 0);
	}
}

int	key_press(int key, t_minirt *rt)
{
	ft_img_refresh(rt);
	if (key == ESC)
		close_program(rt);
	else if (key == E)
		edit_mode(rt);
	else if (key == NUM_1 || key == NUM_2)
		switch_target(rt, key);
	if (rt->editor.flag != NOT_EDIT && rt->editor.flag != EDIT_MODE)
	{
		if (key == UP || key == DOWN || key == LEFT || key == RIGHT || key == L_SQRB || key == R_SQRB)
			key_translate(rt, key);
		if (key == W || key == S || key == A || key == D || key == Z || key == C)
			key_rotate(rt, key);
	}
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_minirt *rt)
{
	size_t	ctr;
	t_coord	ray_vector;
	int		index;

	if (x < 0 || y < 0 || rt->editor.flag == NOT_EDIT || keycode != 1)
		return (0);
	ctr = y * rt->width + x;
	ray_vector = get_ray_vector(rt, rt->file_data->camera, ctr);
	index = get_touchy(rt->file_data, ray_vector);
	if (index == -1)
		return (0);
	rt->editor.flag = OBJ_EDIT;
	set_editing_type(rt, 0);
	rt->editor.target = get_object(rt->file_data->objects, index);
	return (1);
}

void	set_controls(t_minirt *rt)
{
	mlx_key_hook(rt->mlx_win, key_press, rt);
	mlx_mouse_hook(rt->mlx_win, mouse_press, rt);
	mlx_hook(rt->mlx_win, 17, 0, close_program, rt);
}

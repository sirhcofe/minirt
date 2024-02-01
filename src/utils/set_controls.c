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

void	ft_img_refresh(t_minirt *rt)
{
	mlx_destroy_image(rt->mlx, rt->img);
	rt->img = mlx_new_image(rt->mlx, rt->width, rt->height);
	rt->addr = mlx_get_data_addr(rt->img, &(rt->bits_per_pixel),
			&(rt->line_len), &rt->endian);
}

void	switch_target(t_minirt *rt, int keycode)
{
	if (rt->editor.flag == NO_EDIT)
	{
		ft_putstr_fd("Editor mode is not enabled\n", 1);
		return ;
	}
	else if (keycode == MAC_1)
	{
		ft_putstr_fd("Editor target switched to Camera\n", 1);
		rt->editor.flag = CAM_EDIT;
	}
	else if (keycode == MAC_2)
	{
		ft_putstr_fd("Editor target switched to Light\n", 1);
		rt->editor.flag = LIGHT_EDIT;
	}
}

int	key_press(int key, t_minirt *rt)
{
	ft_img_refresh(rt);
	if ((!IS_LINUX && key == MAC_ESC) || (IS_LINUX && key == WIN_ESC))
		close_program(rt);
	else if (key == MAC_E)
		edit_mode(rt, key);
	else if (key == MAC_1 || key == MAC_2)
		switch_target(rt, key);
	else if (key == MAC_UP || key == MAC_DOWN || key == MAC_LEFT
		|| key == MAC_RIGHT || key == MAC_W || key == MAC_S)
		key_translate(rt, key);
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_minirt *rt)
{
	size_t	ctr;
	t_coord	ray_vector;
	int		index;

	if (x < 0 || y < 0 || rt->editor.flag == NO_EDIT || keycode != 1)
		return (0);
	ctr = y * rt->width + x;
	ray_vector = get_ray_vector(rt, rt->file_data->camera, ctr);
	index = get_touchy(rt->file_data, ray_vector);
	if (index == -1)
		return (0);
	ft_putstr_fd("An object has been clicked!\n", 1);
	rt->editor.target = get_object(rt->file_data->objects, index);
	rt->editor.flag = OBJ_EDIT;
	return (1);
}

void	set_controls(t_minirt *rt)
{
	mlx_key_hook(rt->mlx_win, key_press, rt);
	mlx_mouse_hook(rt->mlx_win, mouse_press, rt);
	mlx_hook(rt->mlx_win, 17, 0, close_program, rt);
}

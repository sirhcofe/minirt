/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:32:19 by jthor             #+#    #+#             */
/*   Updated: 2024/02/02 23:19:53 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_grid(t_minirt *rt, size_t ctr)
{
	int	x;
	int	y;
	int	spacing;

	spacing = 5;
	x = ctr % rt->width;
	y = ctr / rt->width;
	if (x % 5 == 0 && y % 5 == 0)
		return (1);
	else
		return (0);
}

void	print_editor(t_minirt *rt)
{
	t_coord	ray_vector;
	size_t	ctr;
	int		index;

	if (rt->file_data->objects != NULL)
	{
		ctr = -1;
		while (++ctr < (rt->height * rt->width))
		{
			if (is_grid(rt, ctr) == 0)
				continue ;
			ray_vector = get_ray_vector(rt, rt->file_data->camera, ctr);
			index = get_touchy(rt->file_data, ray_vector);
			if (index == -1)
				void_pixel(rt, ctr);
			else
				render_pixel(rt, index, ctr, ray_vector);
		}
	}
	else
		empty_protocol(rt);
}

void	edit_mode(t_minirt *rt, int key)
{
	if (rt->editor.flag != NOT_EDIT)
	{
		clear_fixed_line();
		printf("\033[1;32mEditor mode OFF!\033[0m\n");
		printf("\033[1;32mPress [E] to edit again!\033[0m\n\n");
		rt->editor.flag = NOT_EDIT;
		print_image(rt);
		mlx_clear_window(rt->mlx, rt->mlx_win);
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
	}
	else if (rt->editor.flag == NOT_EDIT)
	{
		system("clear");
		printf("\033[1;32mEditor mode ON!\033[0m\n");
		printf("Press [1] - edit camera\n      [2] - edit light\n");
		printf("            Click on any object to transform them\n\n");
		rt->editor.flag = EDIT_MODE;
		set_editing_type(rt, 1);
		print_editor(rt);
		mlx_clear_window(rt->mlx, rt->mlx_win);
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->img, 0, 0);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:02:57 by jthor             #+#    #+#             */
/*   Updated: 2023/09/13 20:02:59 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	add_sphere(t_data *f_data, char **arr)
{
	t_sp	*node;

	if (ft_strncmp(arr[0], "sp", 3) != 0 || ft_arrlen(arr) != 4)
		return (2);
	node = malloc(sizeof(t_sp));
	node->flag = 0;
	assign_coord(&(node->flag), &(node->center), arr[1]);
	node->dia = ft_atod(arr[2]);
	assign_rgb(&(node->flag), &(node->colour), arr[3]);
	if (node->flag == -1 || ft_isdouble(arr[2]) == 0)
	{
		free(node);
		return (2);
	}
	f_data->num_sp += 1;
	ft_lstadd_back(&(f_data->spheres), ft_lstnew(node));
	return (0);
}

int	add_plane(t_data *f_data, char **arr)
{
	t_pl	*node;

	if (ft_strncmp(arr[0], "pl", 3) != 0 || ft_arrlen(arr) != 4)
		return (2);
	node = malloc(sizeof(t_pl));
	node->flag = 0;
	assign_coord(&(node->flag), &(node->point), arr[1]);
	assign_vector(&(node->flag), &(node->normal_vector), arr[2]);
	assign_rgb(&(node->flag), &(node->colour), arr[3]);
	if (node->flag == -1)
	{
		free(node);
		return (2);
	}
	f_data->num_pl += 1;
	ft_lstadd_back(&(f_data->planes), ft_lstnew(node));
	return (0);
}

int	add_cylinder(t_data *f_data, char **arr)
{
	t_cy	*node;

	if (ft_strncmp(arr[0], "cy", 3) != 0 || ft_arrlen(arr) != 6
		|| ft_isdouble(arr[3]) == 0 || ft_isdouble(arr[4]) == 0)
		return (2);
	node = malloc(sizeof(t_cy));
	node->flag = 0;
	assign_coord(&(node->flag), &(node->center), arr[1]);
	assign_vector(&(node->flag), &(node->axis_vector), arr[2]);
	node->dia = ft_atod(arr[3]);
	node->height = ft_atod(arr[4]);
	assign_rgb(&(node->flag), &(node->colour), arr[5]);
	if (node->flag == -1)
	{
		free(node);
		return (2);
	}
	f_data->num_cy += 1;
	ft_lstadd_back(&(f_data->cylinders), ft_lstnew(node));
	return (0);
}

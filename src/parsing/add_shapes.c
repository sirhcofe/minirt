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
	t_sp		n_sp;
	t_object	*node;

	if (ft_strncmp(arr[0], "sp", 3) != 0 || ft_arrlen(arr) != 4)
		return (2);
	n_sp.flag = 0;
	assign_coord(&(n_sp.flag), &(n_sp.center), arr[1]);
	n_sp.dia = ft_atod(arr[2]);
	assign_rgb(&(n_sp.flag), &(n_sp.colour), arr[3]);
	if (n_sp.flag == -1 || ft_isdouble(arr[2]) == 0)
		return (2);
	node = malloc(sizeof(t_object));
	node->e_idx = sp;
	node->obj.sphere = n_sp;
	f_data->num_sp += 1;
	ft_lstadd_back(&(f_data->objects), ft_lstnew(node));
	return (0);
}

int	add_plane(t_data *f_data, char **arr)
{
	t_pl		n_pl;
	t_object	*node;

	if (ft_strncmp(arr[0], "pl", 3) != 0 || ft_arrlen(arr) != 4)
		return (2);
	n_pl.flag = 0;
	assign_coord(&(n_pl.flag), &(n_pl.point), arr[1]);
	assign_vector(&(n_pl.flag), &(n_pl.normal_vector), arr[2]);
	assign_rgb(&(n_pl.flag), &(n_pl.colour), arr[3]);
	if (n_pl.flag == -1)
		return (2);
	node = malloc(sizeof(t_object));
	node->e_idx = pl;
	node->obj.plane = n_pl;
	f_data->num_pl += 1;
	ft_lstadd_back(&(f_data->objects), ft_lstnew(node));
	return (0);
}

int	add_cylinder(t_data *f_data, char **arr)
{
	t_cy		n_cy;
	t_object	*node;

	if (ft_strncmp(arr[0], "cy", 3) != 0 || ft_arrlen(arr) != 6
		|| ft_isdouble(arr[3]) == 0 || ft_isdouble(arr[4]) == 0)
		return (2);
	n_cy.flag = 0;
	assign_coord(&(n_cy.flag), &(n_cy.center), arr[1]);
	assign_vector(&(n_cy.flag), &(n_cy.axis_vector), arr[2]);
	n_cy.dia = ft_atod(arr[3]);
	n_cy.height = ft_atod(arr[4]);
	assign_rgb(&(n_cy.flag), &(n_cy.colour), arr[5]);
	if (n_cy.flag == -1)
		return (2);
	node = malloc(sizeof(t_object));
	node->e_idx = cy;
	node->obj.cylinder = n_cy;
	f_data->num_cy += 1;
	ft_lstadd_back(&(f_data->objects), ft_lstnew(node));
	return (0);
}

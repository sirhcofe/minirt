/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:02:57 by jthor             #+#    #+#             */
/*   Updated: 2024/01/22 14:17:08 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	add_cone(t_data *f_data, char **arr)
{
	t_co		n_co;
	t_object	*node;

	if (ft_arrlen(arr) != 6 || ft_isdouble(arr[3]) == 0
		|| ft_isdouble(arr[4]) == 0)
		return (2);
	n_co.flag = 0;
	assign_coord(&(n_co.flag), &(n_co.vertex), arr[1]);
	assign_vector(&(n_co.flag), &(n_co.axis_vector), arr[2]);
	n_co.radius = ft_atod(arr[3]) / 2;
	n_co.height = ft_atod(arr[4]);
	n_co.base_center = vect_add(n_co.vertex,
			vect_mult(n_co.axis_vector, n_co.height));
	set_coord(&n_co.intsct, 0.0, 0.0, 0.0);
	n_co.intsct_type = 0;
	assign_rgb(&(n_co.flag), &(n_co.colour), arr[5]);
	if (n_co.flag == -1)
		return (2);
	node = malloc(sizeof(t_object));
	node->e_idx = co;
	node->obj.cone = n_co;
	f_data->num_co += 1;
	ft_lstadd_back(&(f_data->objects), ft_lstnew(node));
	return (0);
}

int	add_sphere(t_data *f_data, char **arr)
{
	t_sp		n_sp;
	t_object	*node;

	if (ft_arrlen(arr) != 4)
		return (2);
	n_sp.flag = 0;
	assign_coord(&(n_sp.flag), &(n_sp.center), arr[1]);
	n_sp.dia = ft_atod(arr[2]);
	assign_rgb(&(n_sp.flag), &(n_sp.colour), arr[3]);
	if (n_sp.flag == -1 || ft_isdouble(arr[2]) == 0)
		return (2);
	// n_sp.intsct = ft_calloc(sizeof(t_coord), 1);
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

	if (ft_arrlen(arr) != 4)
		return (2);
	n_pl.flag = 0;
	assign_coord(&(n_pl.flag), &(n_pl.point), arr[1]);
	assign_vector(&(n_pl.flag), &(n_pl.normal_vector), arr[2]);
	assign_rgb(&(n_pl.flag), &(n_pl.colour), arr[3]);
	if (n_pl.flag == -1)
		return (2);
	// n_pl.intsct = ft_calloc(sizeof(t_coord), 1);
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

	if (ft_arrlen(arr) != 6 || ft_isdouble(arr[3]) == 0
		|| ft_isdouble(arr[4]) == 0)
		return (2);
	n_cy.flag = 0;
	assign_coord(&(n_cy.flag), &(n_cy.center), arr[1]);
	assign_vector(&(n_cy.flag), &(n_cy.axis_vector), arr[2]);
	n_cy.radius = ft_atod(arr[3]) / 2;
	n_cy.height = ft_atod(arr[4]);
	set_coord(&n_cy.intsct, 0.0, 0.0, 0.0);
	n_cy.intsct_type = 0;
	assign_rgb(&(n_cy.flag), &(n_cy.colour), arr[5]);
	if (n_cy.flag == -1)
		return (2);
	// n_cy.intsct = ft_calloc(sizeof(t_coord), 1);
	node = malloc(sizeof(t_object));
	node->e_idx = cy;
	node->obj.cylinder = n_cy;
	f_data->num_cy += 1;
	ft_lstadd_back(&(f_data->objects), ft_lstnew(node));
	return (0);
}

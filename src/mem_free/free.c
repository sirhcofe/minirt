/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:02:31 by jthor             #+#    #+#             */
/*   Updated: 2023/11/04 15:22:27 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	free_rt(t_minirt *rt)
{
	mlx_destroy_window(rt->mlx, rt->mlx_win);
	free(rt->img);
	free(rt->addr);
	rt->img = NULL;
	rt->addr = NULL;
	free(rt);
}

void	free_obj_list(void *node)
{
	t_object	*t_node;

	t_node = (t_object *)node;
	if (t_node->e_idx == pl)
		free(t_node->obj.plane.intsct);
	else if (t_node->e_idx == sp)
		free(t_node->obj.sphere.intsct);
	// else if (t_node->e_idx == cy)
	// 	free(t_node->obj.cylinder.intsct);
	else
		write(2, "Unexpected error at free_fdata()\n", 52);
	free(node);
}

void	free_data(t_minirt *rt)
{
	ft_lstclear(&(rt->file_data->objects), free_obj_list);
	free(rt->file_data);
	free_rt(rt);
}

void	free_split(char **head)
{
	int	i;

	i = -1;
	while (head[++i])
		free(head[i]);
	free(head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:02:31 by jthor             #+#    #+#             */
/*   Updated: 2023/09/13 20:02:37 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_rt(t_minirt *rt)
{
	mlx_destroy_window(rt->mlx, rt->mlx_win);
	free(rt->img);
	free(rt->addr);
	rt->img = NULL;
	rt->addr = NULL;
	free(rt);
}

void	free_data(t_minirt *rt)
{
	if (rt->file_data->num_sp > 0)
		ft_lstclear(&(rt->file_data->spheres), free);
	if (rt->file_data->num_pl > 0)
		ft_lstclear(&(rt->file_data->planes), free);
	if (rt->file_data->num_cy > 0)
		ft_lstclear(&(rt->file_data->cylinders), free);
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

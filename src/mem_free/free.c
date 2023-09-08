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
	// if (f_data->num_sp > 0)
	// 	ft_lstclear(&(f_data->spheres), free);
	// if (f_data->num_pl > 0)
	// 	ft_lstclear(&(f_data->planes), free);
	// if (f_data->num_cy > 0)
	// 	ft_lstclear(&(f_data->cylinders), free);
	// free(f_data);
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

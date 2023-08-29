#include "minirt.h"

void	free_data(t_data *f_data)
{
	if (f_data->num_sp > 0)
		ft_lstclear(&(f_data->spheres), free);
	if (f_data->num_pl > 0)
		ft_lstclear(&(f_data->planes), free);
	if (f_data->num_cy > 0)
		ft_lstclear(&(f_data->cylinders), free);
	free(f_data);
}

void	free_split(char **head)
{
	int	i;

	i = -1;
	while (head[++i])
		free(head[i]);
	free(head);
}
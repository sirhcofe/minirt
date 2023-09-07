#include "minirt.h"

/**
 * Error statuses
 * 	1 - Problem with line after entering adding functions
 * 	2 - Garbage line
 * 	3 - More than one C, L, or A.
*/

void	process_line(t_data *f_data, char *line)
{
	int		flag;
	char	**split_ret;

	flag = 2;
	split_ret = ft_split(line, ' ');
	if (ft_strnstr(line, "A ", 2))
		flag = add_ambience(&(f_data->ambience), split_ret);
	else if (ft_strnstr(line, "C ", 2))
		flag = add_camera(&(f_data->camera), split_ret);
	else if (ft_strnstr(line, "L ", 2))
		flag = add_light(&(f_data->light), split_ret);
	else if (ft_strnstr(line, "sp ", 3))
		flag = add_sphere(f_data, split_ret);
	else if (ft_strnstr(line, "pl ", 3))
		flag = add_plane(f_data, split_ret);
	else if (ft_strnstr(line, "cy ", 3))
		flag = add_cylinder(f_data, split_ret);
	free_split(split_ret);
	free(line);
	if (flag)
		error_free(flag, f_data);
}

void	init_data_struct(t_data **f_data)
{
	*(f_data) = malloc(sizeof(t_data));
	(*f_data)->num_sp = 0;
	(*f_data)->num_pl = 0;
	(*f_data)->num_cy = 0;
	(*f_data)->spheres = NULL;
	(*f_data)->planes = NULL;
	(*f_data)->cylinders = NULL;
	(*f_data)->ambience.flag = 0;
	(*f_data)->camera.flag = 0;
	(*f_data)->light.flag = 0;
}

t_data	*parse_file(char *file)
{
	t_data	*ret;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		arg_error(2);
	init_data_struct(&ret);
	while (1 == 1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n') ;
		else
			process_line(ret, ft_strtrim(line, "\n"));
		free(line);
	}
	close(fd);
	return (ret);
}
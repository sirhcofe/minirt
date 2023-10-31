/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:04:00 by jthor             #+#    #+#             */
/*   Updated: 2023/09/13 20:04:02 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	split_ret = ft_split_alt(line, " \t");
	if (ft_strncmp(split_ret[0], "A", 2) == 0)
		flag = add_ambience(&(f_data->ambience), split_ret);
	else if (ft_strncmp(split_ret[0], "C", 2) == 0)
		flag = add_camera(&(f_data->camera), split_ret);
	else if (ft_strncmp(split_ret[0], "L", 2) == 0)
		flag = add_light(&(f_data->light), split_ret);
	else if (ft_strncmp(split_ret[0], "sp", 3) == 0)
		flag = add_sphere(f_data, split_ret);
	else if (ft_strncmp(split_ret[0], "pl", 3) == 0)
		flag = add_plane(f_data, split_ret);
	else if (ft_strncmp(split_ret[0], "cy", 3) == 0)
		flag = add_cylinder(f_data, split_ret);
	free_split(split_ret);
	free(line);
	if (flag)
		error_free(flag, f_data);
}

t_data	*parse_file(char *file)
{
	t_data	*ret;
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		arg_error("Invalid .rt file.\n");
	init_data_struct(&ret);
	while (1 == 1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] == '\n')
			;
		else
			process_line(ret, ft_strtrim(line, "\n"));
		free(line);
	}
	close(fd);
	return (ret);
}

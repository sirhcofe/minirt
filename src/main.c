/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:31:29 by chenlee           #+#    #+#             */
/*   Updated: 2023/09/07 17:01:38 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void arg_check(int argc, char **argv)
{
	char	*period;

	if (argc != 2)
		error("Usage: ./miniRT <MAP FILE>\n");
	period = ft_strchr(argv[1], '.');
	if (!period)
		error("Invalid map file.\n");
	if (ft_strncmp(period, ".rt", 4) != 0)
		error("Invalid map file.\n");
}

int	main(int argc, char **argv)
{
	t_minirt	*rt;

	arg_check(argc, argv);
	rt = init_mlx_window();
	// parse_file(&file_data, argv[1]);
	// free_data(&file_data);
	// exit(EXIT_SUCCESS);
	set_controls(rt);
	mlx_loop(rt->mlx);
}

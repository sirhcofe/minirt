/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:05:18 by jthor             #+#    #+#             */
/*   Updated: 2023/09/13 20:05:20 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	arg_error(char *err_msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

void	error_free(int status, t_data *f_data)
{
	ft_putstr_fd("Error\n", 2);
	if (status == 1)
		ft_putstr_fd("Problematic object found in file\n", 2);
	else if (status == 2)
		ft_putstr_fd("Unrecognised object description\n", 2);
	else if (status == 3)
		ft_putstr_fd("More than one Camera, Light or Ambience object\n", 2);
	ft_lstclear(&(f_data->objects), free_obj_list);
	free(f_data);
	exit(EXIT_FAILURE);
}

// For testing purposes
// void	arg_error(char *err_msg)
// {
// 	ft_putstr_fd("Error\n", 2);
// 	ft_putstr_fd(err_msg, 2);
// 	system("leaks minirt");
// 	exit(EXIT_FAILURE);
// }

// void	error_free(int status, t_data *f_data)
// {
// 	ft_putstr_fd("Error\n", 2);
// 	if (status == 1)
// 		ft_putstr_fd("Problematic object found in file\n", 2);
// 	else if (status == 2)
// 		ft_putstr_fd("Unrecognised object description\n", 2);
// 	else if (status == 3)
// 		ft_putstr_fd("More than one Camera, Light or Ambience object\n", 2);
// 	ft_lstclear(&(f_data->objects), free_obj_list);
// 	free(f_data);
// 	system("leaks minirt");
// 	exit(EXIT_FAILURE);
// }

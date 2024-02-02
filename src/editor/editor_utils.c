/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 22:53:22 by chenlee           #+#    #+#             */
/*   Updated: 2024/02/02 23:31:31 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_fixed_line(void)
{
	printf("\033[A");
	printf("\033[K");
}

void	set_editing_type(t_minirt *rt, int first_time_printing)
{
	const char	*color[5] = {"\033[1;34m", "\033[1;33m", "\033[1;35m", "\033[1;32m"};
	const char	*type[5] = {"None", "Camera", "Light", "Object"};

	if (!first_time_printing)
	{
		printf("\033[A");
		printf("\033[K");
	}
	printf("\033[1;36mCurrently editing: %s%s\033[0m\n",
							color[rt->editor.flag], type[rt->editor.flag]);
}

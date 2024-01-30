/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:10:15 by jthor             #+#    #+#             */
/*   Updated: 2024/01/30 17:10:17 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define BUFFER_SIZE 50
# define MAX_INT 2147483647

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# include "objects.h"
# include "driver.h"
# include "init.h"
# include "mathematics.h"
# include "mem_free.h"
# include "parse.h"
# include "ray_tracing.h"
# include "utils.h"

void	set_controls(t_minirt *rt);

#endif

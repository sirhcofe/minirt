/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:08:47 by jthor             #+#    #+#             */
/*   Updated: 2024/01/30 17:08:49 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_FREE_H
# define MEM_FREE_H

# include "objects.h"

/********************************** free.c **********************************/

/**
 * @brief Freeing function for the object linked list located in file_data.
 * This function is intended to be used with ft_lstclear().
 * @return Function does not return.
 * @param node The content of the linked list.
 */
void	free_obj_list(void *node);
/**
 * @brief Function frees all malloc'd data related to this project.
 * @return Function does not return.
 * @param rt Pointer to the t_minirt struct that holds everything.
 */
void	free_data(t_minirt *rt);
/**
 * @brief Function frees char double-array memory.
 * @return Function does not return.
 * @param head Double-char-array to be freed.
 */
void	free_split(char **head);

#endif

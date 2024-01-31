/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:57:59 by jthor             #+#    #+#             */
/*   Updated: 2024/01/30 17:58:02 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "objects.h"

/********************************** error.c **********************************/

/**
 * @brief Exits the program with an error message for errors regarding
 * command line arguments
 * @return Function returns nothing
 * @param err_msg The error message to display
*/
void	arg_error(char *err_msg);
/**
 * @brief Exits the program after freeing the t_data struct from memory
 * @return Function returns nothing
 * @param flag The flag that determins which error message to display
 * @param f_data Pointer to the t_data variable to be freed
*/
void	error_free(int flag, t_data *f_data);

/****************************** ft_split_alt.c ******************************/

/**
 * @brief Splits a string according to the delimiters passed.
 * @return A null-terminated, malloc'd array of strings after the parent
 * string is split.
 * @param str The string to be split.
 * @param sep The delimiter characters, parsed as a string.
*/
char	**ft_split_alt(char *str, char *sep);

/****************************** general_utils.c ******************************/

/**
 * @brief Converts a string to a double
 * @return A double
 * @param str The string to be converted
*/
double	ft_atod(const char *str);
/**
 * @brief Counts the length of a null-terminated array of strings
 * @return The length of the array, not inclusive of the null element
 * @param arr A pointer to the first element of the array of strings
*/
int		ft_arrlen(char **arr);
/**
 * @brief Checks if a number is within a specified range, limits included
 * @return An int that is to be used as a flag
 * @retval 0 if the number is outside the range
 * @retval 1 if the number is within the range
 * @param num The number to be checked
 * @param low The lower limit of the range
 * @param high The upper limit of the range
*/
int		ft_inrange(double num, double low, double high);
/**
 * @brief Checks if a string is a rational number or integer. A rational
 * number is defined here as either a positive or negative number that has
 * only one period (.) between two or more numbers
 * @return An int that is to be used as a flag
 * @retval 0 if the number is not a valid double
 * @retval 1 if the number is a valid double
 * @param str The string to be checked
*/
int		ft_isdouble(char *str);

/****************************** get_next_line.c ******************************/

/**
 * @brief Reads a file and returns its contents line by line
 * @return A malloc'd string representing a line from the read file
 * @param fd The file descriptor of the file to be read
*/
char	*get_next_line(int fd);

/****************************** set_controls.c ******************************/

void	set_controls(t_minirt *rt);

#endif

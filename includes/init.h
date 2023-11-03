#ifndef INIT_H
#define INIT_H

#include "objects.h"

/***************************** initialization.c *****************************/

/**
 * @brief Initialization of the mlx graphical system with the MiniLibX library
 * along with a struct initialized for data extraction from `.rt` file.
 * 
 * @return Function return a struct containing the mlx graphical system and
 * data extraction from `.rt` file
*/
t_minirt	*init_mlx_window(void);
/**
 * @brief Initialises the t_data struct variable and its data to 0
 * @return Function does not return
 * @param f_data Double pointer to the t_data variable
*/
void	init_data_struct(t_data **f_data);

#endif
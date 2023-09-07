#ifndef MINIRT_H
# define MINIRT_H

# define BUFFER_SIZE 50

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# include "objects.h"

/* -.- Memory Freeing -.- */
// free.c
/**
 * @brief Function frees the t_data struct allocated in memory
 * @return Function does not return
 * @param f_data Pointer to t_data variable to be freed
*/
void	free_data(t_data *f_data);
/**
 * @brief Function frees char double-array memory
 * @return Function does not return
 * @param head double-char-array to be freed
*/
void	free_split(char **head);

/* -.- Parsing -.- */

// add_shapes.c
/**
 * @brief Adds a sphere object to the t_data struct
 * @return Returns an int flag to be used for error detection and management
 * @retval 2 if the line is not configured properly
 * @retval 0 if object is added successfully
 * @param f_data Pointer to the t_data variable
 * @param arr Double-char-array that specifies a sphere object
*/
int		add_sphere(t_data *f_data, char **arr);
/**
 * @brief Adds a plane object to the t_data struct
 * @return Returns an int flag to be used for error detection and management
 * @retval 2 if the line is not configured properly
 * @retval 0 if object is added successfully
 * @param f_data Pointer to the t_data variable
 * @param arr Double-char-array that specifies a plane object
*/
int		add_plane(t_data *f_data, char **arr);
/**
 * @brief Adds a cylinder object to the t_data struct
 * @return Returns an int flag to be used for error detection and management
 * @retval 2 if the line is not configured properly
 * @retval 0 if object is added successfully
 * @param f_data Pointer to the t_data variable
 * @param arr Double-char-array that specifies a cylinder object
*/
int		add_cylinder(t_data *f_data, char **arr);

// add_single.c
/**
 * @brief Adds an ambience object to the t_data struct
 * @return An int flag to be used for error detection and management
 * @retval 3 if object already exists
 * @retval 2 if the line is not configured properly
 * @retval 0 if object is added successfully
 * @param f_data Pointer to the t_data variable
 * @param arr Double-char-array that specifies an ambience object
*/
int		add_ambience(t_amb *obj , char **arr);
/**
 * @brief Adds a camera object to the t_data struct
 * @return Returns an int flag to be used for error detection and management
 * @retval 3 if object already exists
 * @retval 2 if the line is not configured properly
 * @retval 0 if object is added successfully
 * @param f_data Pointer to the t_data variable
 * @param arr Double-char-array that specifies a camera object
*/
int		add_camera(t_cam *obj, char **arr);
/**
 * @brief Adds a light object to the t_data struct
 * @return Returns an int flag to be used for error detection and management
 * @retval 3 if object already exists
 * @retval 2 if the line is not configured properly
 * @retval 0 if object is added successfully
 * @param f_data Pointer to the t_data variable
 * @param arr Double-char-array that specifies a light object
*/
int		add_light(t_light *obj, char **arr);

// parse_helpers.c
/**
 * @brief Converts a string to a double and checks if it is within the
 * specified range for a ratio
 * @return A double in the range of [0.0, 1.0]
 * @param flag Pointer to the object's flag variable for error detection and
 * management
 * @param str The string to be converted to a double
*/
double	assign_ratio(int *flag, char *str);
/**
 * @brief Converts a string to an RGB object and checks if it is formatted
 * correctly
 * @return Function does not return
 * @param flag Pointer to the object's flag variable for error detection and
 * management
 * @param obj Pointer to the t_rgb struct within the object's struct
 * @param str The string to be converted to a t_rgb struct
*/
void	assign_rgb(int *flag, t_rgb *obj, char *str);
/**
 * @brief Converts a string to a coord object and checks if it is formatted
 * correctly
 * @return Function does not return
 * @param flag Pointer to the object's flag variable for error detection and
 * management
 * @param obj Pointer to the t_coord struct within the object's struct
 * @param str The string to be converted to a t_coord struct
*/
void	assign_coord(int *flag, t_coord *obj, char *str);
/**
 * @brief Converts a string to a vector object and checks if it is formatted
 * correctly
 * @return Function does not return
 * @param flag Pointer to the object's flag variable for error detection and
 * management
 * @param obj Pointer to the t_coord struct within the object's struct
 * @param str The string to be converted to a t_coord struct
*/
void	assign_vector(int *flag, t_coord *obj, char *str);
/**
 * @brief Converts a string to a double and checks if it is within the
 * specified range for an FOV
 * @return A double in the range of [0.0, 180.0]
 * @param flag Pointer to the object's flag variable for error detection and
 * management
 * @param str The string to be converted to a double
*/
double	assign_fov(int *flag, char *str);

/* parse.c */
/**
 * @brief Takes a line from the file, and determines if it is an element or not
 * @return Function does not return
 * @param f_data Pointer to the t_data variable
 * @param line The line read from the .rt file.
*/
void	process_line(t_data *f_data, char *line);
/**
 * @brief Initialises the t_data struct variable and its data to 0
 * @return Function does not return
 * @param f_data Double pointer to the t_data variable
*/
void	init_data_struct(t_data **f_data);
/**
 * @brief Opens the .rt file and processes its contents line by line
 * @return The pointer to a t_data struct initialised and allocated in memory
 * @param file The name of the .rt file to be opened
*/
t_data	*parse_file(char *file);

/* -.- Utils -.- */

// general_utils.c
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

// parse_utils.c
/**
 * @brief Checks if a string is formatted as an RGB [xxx,xxx,xxx]
 * @warning Does not check if the integer parts are within the colour range
 * [0, 255]
 * @return An int that is to be used as a flag
 * @retval 0 if the string is not in an RGB format
 * @retval 1 if the string follows the RGB format
 * @param str The string to be checked
*/
int		ft_isrgb(char *str);
/**
 * @brief Sets the values of a t_coord struct
 * @return Function returns nothing
 * @param obj Pointer to the t_coord variable
 * @param temp Pointer to an array of doubles that represent (x, y, z)
*/
void	set_coord(t_coord *obj, double *temp);

/* error.c */
/**
 * @brief Exits the program with an error message for errors regarding
 * command line arguments
 * @return Function returns nothing
 * @param status The flag that determines which error message to display
*/
void	arg_error(int status);
/**
 * @brief Exits the program after freeing the t_data struct from memory
 * @return Function returns nothing
 * @param flag The flag that determins which error message to display
 * @param f_data Pointer to the t_data variable to be freed
*/
void	error_free(int flag, t_data *f_data);

/* get_next_line.c */
/**
 * @brief Reads a file and returns its contents line by line
 * @return A malloc'd string representing a line from the read file
 * @param fd The file descriptor of the file to be read
*/
char	*get_next_line(int fd);

#endif
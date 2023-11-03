#ifndef PARSE_H
#define PARSE_H

#include "objects.h"

/******************************* add_shapes.c *******************************/

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

/******************************* add_single.c *******************************/

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

/****************************** parse_helpers.c ******************************/

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

/********************************** parse.c **********************************/

/**
 * @brief Takes a line from the file, and determines if it is an element or not
 * @return Function does not return
 * @param f_data Pointer to the t_data variable
 * @param line The line read from the .rt file.
*/
void	process_line(t_data *f_data, char *line);
/**
 * @brief Opens the .rt file and processes its contents line by line
 * @return The pointer to a t_data struct initialised and allocated in memory
 * @param file The name of the .rt file to be opened
*/
t_data	*parse_file(char *file);

/******************************* parse_utils.c *******************************/

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
 * @param x The x-component of the vector
 * @param y The y-component of the vector
 * @param z The z-component of the vector
*/
void	set_coord(t_coord *obj, double x, double y, double z);

#endif
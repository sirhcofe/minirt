#ifndef MINIRT_H
#define MINIRT_H

#define BUFFER_SIZE 50

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include "libft.h"
#include "mlx.h"
#include "objects.h"

#define MAX_INT 2147483647

/*************************** -.- initialization -.- ***************************/

/**
 * @brief Initialization of the mlx graphical system with the MiniLibX library
 * along with a struct initialized for data extraction from `.rt` file.
 * 
 * @return Function return a struct containing the mlx graphical system and
 * data extraction from `.rt` file
*/
t_minirt	*init_mlx_window(void);

/******************************* -.- Parsing -.- ******************************/

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

// parse.c
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

/**************************** -.- Mathematics -.- *****************************/

// geom_trans.c
/**
 * @brief Function calculates the translation vector to move an object to the
 * origin in a 3D Cartesian plane.
 * @param object The object's current x,y,z position
 * @return 3D vector (x, y, z) representing the translation needed to bring the
 * object to the origin.
*/
t_coord	translation(t_coord object);
/**
 * @brief Function applies Rodrigues' rotation formula to find the new position
 * of a vector after it has been rotated about an arbitrary axis.
 * @param vector The original 3D vector.
 * @param angle The angle of rotation in radians.
 * @return Function returns a new position of a vector after it has been
 * rotated.
*/
t_coord	rotation(t_coord *vector, double angle);

// vector_algebra.c
/**
 * @brief Function performs dot product operation on two vectors in a 3D
 * oriented Euclidean vector space.
 * @param a The first vector.
 * @param b The second vector.
 * @return Function returns a scalar number that is a measure of how closely the
 * two vectors align.
*/
double	dot_prod(t_coord a, t_coord b);
/**
 * @brief Function performs cross product operation on two vectors in a 3D
 * oriented Euclidean vector space.
 * @param a The first vector.
 * @param b The second vector.
 * @return Function returns a new vector that is perpendicular to both a and b,
 * thus normal to the plane containing them (assuming a and b are linearly
 * independent).
*/
t_coord	cross_prod(t_coord a, t_coord b);
t_coord	normalize(t_coord a);

// vector_arithmetic.c
/**
 * @brief Function performs scalar multiplication on a vector, where each
 * components of the vector is multiplied by the specified value.
 * @param vector The vector for multiplication.
 * @param value The value to be multiplied for each component of the vector.
 * @return Function returns a new vector as the product of the arithmetic
 * operation.
*/
t_coord	vect_mult(t_coord vector, double value);
/**
 * @brief Function performs summation of two (or three) vectors.
 * @param a The first vector.
 * @param b The second vector.
 * @return Function returns a resulting vector of the vectors parsed.
*/
t_coord vect_add(t_coord a, t_coord b);
/**
 * @brief Function performs subtraction of two (or three) vectors.
 * @param a The first vector.
 * @param b The second vector.
 * @return Function returns a resulting vector of the vectors parsed.
*/
t_coord vect_subt(t_coord a, t_coord b);

/*************************** -.- Memory Freeing -.- ***************************/

/**
 * @brief Function frees all malloc'd data related to this project.
 * @return Function does not return.
 * @param rt Pointer to the t_minirt struct that holds everything.
 */
void free_data(t_minirt *rt);
/**
 * @brief Function frees char double-array memory.
 * @return Function does not return.
 * @param head Double-char-array to be freed.
 */
void free_split(char **head);

/******************************* -.- Driver -.- *******************************/

// print_img.c
/**
 * @brief The driver function for rendering the image to the screen.
 * @return Function does not return.
 * @param rt Pointer to the t_minirt struct that holds everything.
*/
void	print_image(t_minirt *rt);
/**
 * @brief Goes through all shapes (if any) and finds which one is closest to
 * the camera following the path of the ray passed as a parameter
 * @return Returns the index of the closest object from the camera using the
 * path of the ray
 * @param f_data Pointer to the t_data struct for shortcut purposes
 * @param ray_vector The directional vector of the ray that originates from
 * the camera.
 */
int		get_touchy(t_data *f_data, t_coord *ray_vector);
/**
 * @brief Function that prints an empty map, in the absence of objects.
 * @return Function does not return.
 * @param rt Pointer to the t_minirt struct that holds everything.
*/
void	empty_protocol(t_minirt *rt);
/**
 * @brief Goes through a linked list of an object and with the ray directional
 * vector, applies the appropriate intersection function on each of them.
 * @return Function does not return
 * @param data Pointer to an array of three doubles;
 * @param data[0] The index of the closest object from the camera, following
 * the ray
 * @param data[1] Counter to keep track of the objects while looping through
 * the linked list
 * @param data[2] The distance between the closest object and the camera,
 * following the ray
 * @param f_data Temporary struct to hold the ray vector, camera object and
 * linked list of the object
 * @param f Pointer to the intersection function
 */
void	scroll_obj(double *data[3], t_intrsct f_data, double (*f)(t_coord *, void *, t_cam));


int	get_cy_dist(double *dist, t_coord ray_vec, t_coord ray_ori, t_cy *cy);

// draw.c
/**
 * @brief Function that replaces mlx_pixel_put cause its dong.
 * @return Function does not return.
 * @param rt Pointer to the t_minirt struct that holds everything.
 * @param x The x-coordinate of the pixel to be coloured.
 * @param y The y-coordinate of the pixel to be coloured.
 * @param colour The intended colour of the pixel.
*/
void	put_pxl(t_minirt *rt, int x, int y, int colour);
/**
 * @brief Renders the pixel if the ray that comes from it goes to infinity
 * @return Function does not return.
 * @param rt Pointer to the t_minirt struct that holds everything.
 * @param idx Location of the pixel, to be broken down to the x and y values
 * 
*/
void	void_pixel(t_minirt *rt, int idx);

/******************************** -.- Utils -.- *******************************/

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
 * @param x The x-component of the vector
 * @param y The y-component of the vector
 * @param z The z-component of the vector
*/
void	set_coord(t_coord *obj, double x, double y, double z);

/* error.c */
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

/* get_next_line.c */
/**
 * @brief Reads a file and returns its contents line by line
 * @return A malloc'd string representing a line from the read file
 * @param fd The file descriptor of the file to be read
*/
char	*get_next_line(int fd);

/******************************* -.- Shapes -.- *******************************/

/* plane_intersection.c */

/**
 * @brief Determines if the ray_vector intersects with the plane and calculates
 * the distance between them if there is an intersection
 * @param ray_vector The directional vector from the viewer
 * @param plane The struct holding the data of the plane object
 * @param camera The camera object
 * @retval 0 if there is no intersection, a positive number of type double otherwise
 * @return The distance between the viewer amd the object, if it is within the
 * field of vision.
*/
double	get_pl_dist(t_coord *ray_vector, t_pl *plane, t_cam camera);

#endif
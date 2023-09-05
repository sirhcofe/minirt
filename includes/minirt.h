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

/* -.- Memory Freeing -.- */

/**
 * hello world
 */
void free_data(t_data *f_data, t_minirt *rt);
/**
 * @brief Function frees char double-array memory.
 * @return Function does not return.
 * @param head Double-char-array to be freed.
 */
void free_split(char **head);

/* -.- Parsing -.- */

// add_shapes.c
int add_sphere(t_data *f_data, char **arr);
int add_plane(t_data *f_data, char **arr);
int add_cylinder(t_data *f_data, char **arr);

// add_single.c
int add_ambience(t_amb *obj, char **arr);
int add_camera(t_cam *obj, char **arr);
int add_light(t_light *obj, char **arr);

// parse_helper.c
double assign_ratio(int *flag, char *str);
void assign_rgb(int *flag, t_rgb *obj, char *str);
void assign_coord(int *flag, t_coord *obj, char *str);
void assign_vector(int *flag, t_coord *obj, char *str);
double assign_fov(int *flag, char *str);

// parse.c
void parse_file(t_data *f_data, char *file);

/* -.- mlx -.- */

/**
 * @brief Initialization of graphic application on screen using MiniLibX
 * library. 
 * 
 * @param rt The main struct containing all data relevant to project.
 * @return Function does not return.
*/
void	init_mlx_window(t_minirt *rt);

/* -.- Utils -.- */

// general_utils.c
double ft_atod(const char *str);
int ft_arrlen(void *arr);
int ft_inrange(double num, double low, double high);
int ft_isdouble(char *str);

// parse_utils.c
int ft_isrgb(char *str);
void set_coord(t_coord *obj, double *temp);

// set_controls.c
void	set_controls(t_data *f_data, t_minirt *rt);

/* error.c */
void error(char *err_msg);
void error_free(int flag, t_data *f_data, char *gnl);

/* get_next_line.c */
char *get_next_line(int fd);

#endif
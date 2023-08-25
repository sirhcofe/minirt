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
void	free_data(t_data *f_data);
void	free_split(char **head);

/* -.- Parsing -.- */

// add_single.c
int		add_ambience(t_amb *obj , char **arr);
int		add_camera(t_cam *obj, char **arr);
int		add_light(t_light *obj, char **arr);

// parse_helper.c
double	assign_ratio(int *flag, char *str);
void	assign_rgb(int *flag, t_rgb *obj, char *str);
void	assign_coord(int *flag, t_coord *obj, char *str);
void	assign_vector(int *flag, t_coord *obj, char *str);
double	assign_fov(int *flag, char *str);

/* parse.c */
void	parse_file(t_data *f_data, char *file);

/* -.- Utils -.- */

// general_utils.c
double	ft_atod(const char *str);
int		ft_arrlen(void *arr);
int		ft_inrange(double num, double low, double high);
int		ft_isdouble(char *str);

// parse_utils.c
int		ft_isrgb(char *str);
void	set_coord(t_coord *obj, double *temp);

/* error.c */
void	error(int status);
void	error_free(int flag, t_data *f_data, char *gnl);

/* get_next_line.c */
char	*get_next_line(int fd);

#endif
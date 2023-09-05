#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_rgb
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}	t_rgb;

typedef struct s_coord
{
	double	x;
	double	y;
	double	z;
	double	w;
}	t_coord;

typedef struct s_amb
{
	int		flag;
	double	ratio;
	t_rgb	colour;
}	t_amb;

typedef struct s_cam
{
	int		flag;
	t_coord	point;
	t_coord	orient_vector;
	double	fov;
}	t_cam;

typedef struct s_light
{
	int		flag;
	t_coord	point;
	double	ratio;
	t_rgb	colour;
}	t_light;

typedef struct s_sp
{
	int		flag;
	t_coord	center;
	double	dia;
	t_rgb	colour;
}	t_sp;

typedef struct s_pl
{
	int		flag;
	t_coord	point;
	t_coord	normal_vector;
	t_rgb	colour;
}	t_pl;

typedef struct s_cy
{
	int		flag;
	t_coord	center;
	t_coord	axis_vector;
	double	dia;
	double	height;
	t_rgb	colour;
}	t_cy;

typedef struct s_data
{
	int		num_sp;
	int		num_pl;
	int		num_cy;
	t_amb	ambience;
	t_cam	camera;
	t_light	light;
	t_list	*spheres;
	t_list	*planes;
	t_list	*cylinders;
}	t_data;

typedef struct s_minirt
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	int		window_h;
	int		window_w;
	t_data	*file_data;
}	t_minirt;

#endif
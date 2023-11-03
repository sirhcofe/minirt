#ifndef DRIVER_H
#define DRIVER_H

#include "objects.h"

/******************************** print_img.c ********************************/

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
int	get_touchy(t_data *f_data, t_coord *ray_vector);

/********************************** draw.c **********************************/

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

#endif
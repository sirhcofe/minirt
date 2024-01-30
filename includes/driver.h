/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   driver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthor <jthor@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:06:42 by jthor             #+#    #+#             */
/*   Updated: 2024/01/30 17:06:44 by jthor            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRIVER_H
# define DRIVER_H

# include "objects.h"

/******************************** print_img.c ********************************/

/**
 * @brief The driver function for rendering the image to the screen.
 * @return Function does not return.
 * @param rt Pointer to the t_minirt struct that holds everything.
*/
void	print_image(t_minirt *rt);
/**
 * @brief Populates the image with pixels using the ambient light's RGB.
 * @return Function does not return.
 * @param rt Pointer to the t_minirt struct.
 */
void	empty_protocol(t_minirt *rt);
/**
 * @brief Goes through all shapes (if any) and finds which one is closest to
 * the camera following the path of the ray passed as a parameter
 * @return Returns the index of the closest object from the camera using the
 * path of the ray, -1 otherwise.
 * @param f_data Pointer to the t_data struct for shortcut purposes
 * @param ray_vector The directional vector of the ray that originates from
 * the camera.
 */
int		get_touchy(t_data *f_data, t_coord ray_vector);
/**
 * @brief Determines which function to call based on the object specifier
 * in the union.
 * @return The distance from the origin of the ray to an object, if there is
 * an intersection.
 * @retval INFINITY if there is no intersection, a positive double otherwise.
 * @param r_vect The directional vector of the ray, normalised. 
 * @param ray_ori The origin of the ray.
 * @param lst_content The pointer to the content of the linked list.
 */
double	get_curr_dist(t_coord r_vect, t_coord ray_ori, void *lst_content);
/**
 * @brief Uses the current counter to infer the x and y values of a pixel on
 * the screen, and returns the directional vector connecting the camera
 * viewpoint to the pixel.
 * @param rt The pointer to the t_minirt struct.
 * @param cam The camera object.
 * @param ctr The counter keeping track of which pixel to colour.
 * @return The normalised directional vector.
 */
t_coord	get_ray_vector(t_minirt *rt, t_cam cam, size_t ctr);

/********************************** draw.c **********************************/

/**
 * @brief Blends the individual RGB values using bitshifting and bitwise OR
 * operations
 * @return Returns the int representation of the RGB blend
 * @param t transparency
 * @param r red concentration
 * @param g green concentration
 * @param b blue concentration
*/
int		create_colour(int t, int r, int g, int b);
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
 * @param rt Pointer to the t_minirt struct.
 * @param idx Location of the pixel, to be broken down to the x and y values
*/
void	void_pixel(t_minirt *rt, int idx);

#endif

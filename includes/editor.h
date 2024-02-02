#ifndef EDITOR_H
# define EDITOR_H

# include "objects.h"

/******************************** translate.c ********************************/

void	translate_cam(t_minirt *rt, int key);
void	key_translate(t_minirt *rt, int key);

/********************************** rotate.c **********************************/

void	key_rotate(t_minirt *rt, int key);

/********************************** editor.c **********************************/

void	print_editor(t_minirt *rt);
void	edit_mode(t_minirt *rt, int key);

/******************************* editor_utils.c *******************************/

void	clear_fixed_line(void);
void	set_editing_type(t_minirt *rt, int first_time_printing);

#endif
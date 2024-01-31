#ifndef EDITOR_H
# define EDITOR_H

# include "objects.h"

/******************************** translate.c ********************************/

void	translate_cam(t_minirt *rt, int key);
void	key_translate(t_minirt *rt, int key);

/********************************* rotate.c *********************************/

void	rotate_cam(t_minirt *rt, int key);

/********************************* editor.c *********************************/

void	print_editor(t_minirt *rt);
void	edit_mode(t_minirt *rt, int key);

#endif
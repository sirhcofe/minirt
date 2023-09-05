# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 21:28:59 by chenlee           #+#    #+#              #
#    Updated: 2023/09/06 00:46:04 by chenlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME		:=	$(shell uname)

ifeq ($(UNAME), Linux)
	LIBX = minilibx/minilibx_linux/
	COMPILE = -L$(LIBX) -lmlx_Linux -L/usr/lib -I$(LIBX) -lXext -lX11 -lm -lz
	PREBUILD = xrandr | awk '/XWAYLAND0 connected/ {getline; print $$1}' > resolution && echo Linux > os
endif
ifeq ($(UNAME), Darwin)
	LIBX = minilibx/minilibx_macos/
	COMPILE = -L$(LIBX) -lmlx -framework OpenGL -framework AppKit
	PREBUILD = system_profiler SPDisplaysDataType | awk '/Resolution/ {print $$2, $$3, $$4}' > resolution && echo Darwin > os
endif

$(shell $(PREBUILD))

NAME		=	libminirt.a
FLAGS		=	
OBJS_DIR	=	objects/
OBJS		=	$(addprefix $(OBJS_DIR), $(notdir $(SRC:.c=.o)))

# source files here #
SRC			=	error.c				\
				mlx_window_init.c	\
				get_next_line.c		\
				free.c				\
				add_shapes.c		\
				add_single.c		\
				parse_helpers.c		\
				parse.c				\
				general_utils.c		\
				parse_utils.c		\
				set_controls.c

# source directory here #
SRC_DIR		=	$(LIBX)			\
				src				\
				src/init			\
				src/mem_free	\
				src/parsing		\
				src/utils		\

vpath %.c $(SRC_DIR)

INCLUDES	=	-Ilibft -Iincludes

all:			$(NAME) minirt

$(NAME):		$(OBJS)
			@make -C $(LIBX) all
			@make -C libft/ all
			@ar rc $(NAME) $(OBJS)

$(OBJS_DIR)%.o:	%.c
			@mkdir -p $(OBJS_DIR)
			@echo "Compiling: $<"
			@gcc $(FLAGS) -I$(LIBX) $(INCLUDES) -c $< -o $@

minirt:		src/main.c $(OBJS)
			@echo "Compiling: src/main.c"
			@gcc $(FLAGS) -g3 src/main.c -L. -lminirt -Llibft -lft $(INCLUDES) $(COMPILE) -o minirt

clean:
			@rm -rf objects resolution os
			@make -C $(LIBX) clean
			@make -C libft/ clean
			@echo "clean done!"

fclean:		clean
			@make -C libft/ fclean
			@rm -rf $(NAME) minirt
			@echo "fclean done!"

re:			fclean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 21:28:59 by chenlee           #+#    #+#              #
#    Updated: 2023/11/03 00:19:40 by chenlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME		:=	$(shell uname)

ifeq ($(UNAME), Linux)
	LIBX = minilibx/minilibx_linux/
	COMPILE = -L$(LIBX) -lmlx_Linux -L/usr/lib -I$(LIBX) -lXext -lX11 -lm -lz
endif
ifeq ($(UNAME), Darwin)
	LIBX = minilibx/minilibx_macos/
	COMPILE = -L$(LIBX) -lmlx -framework OpenGL -framework AppKit
endif

NAME		=	libminirt.a
FLAGS		=	-fsanitize=address -g3
OBJS_DIR	=	objects/
OBJS		=	$(addprefix $(OBJS_DIR), $(notdir $(SRC:.c=.o)))

# source files here #
# SRC			=	error.c				\
# 				initialization.c	\
# 				get_next_line.c		\
# 				parse.c				\
# 				parse_helpers.c		\
# 				add_shapes.c		\
# 				add_single.c		\
# 				general_utils.c		\
# 				parse_utils.c		\
# 				geom_trans.c		\
# 				vector_algebra.c	\
# 				vector_arithmetic.c	\
# 				get_cy_dist.c		\
# 				set_controls.c		\
# 				free.c

SRC			=	error.c				\
				initialization.c	\
				get_next_line.c		\
				geom_trans.c		\
				vector_algebra.c	\
				vector_arithmetic.c	\
				get_cy_dist.c		\
				get_sp_dist.c		\
				set_controls.c		\
				free.c

# source directory here #
SRC_DIR		=	$(LIBX)			\
				src				\
				src/init		\
				src/math		\
				src/mem_free	\
				src/ray_tracing	\
				src/utils		\
				# src/parsing		\

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
			@rm -rf objects resolution
			@make -C $(LIBX) clean
			@make -C libft/ clean
			@echo "clean done!"

fclean:		clean
			@make -C libft/ fclean
			@rm -rf $(NAME) minirt
			@echo "fclean done!"

re:			fclean all

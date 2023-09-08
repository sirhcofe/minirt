# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/14 21:28:59 by chenlee           #+#    #+#              #
#    Updated: 2023/08/14 21:33:11 by chenlee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# UNAME		:=	$(shell uname)

# ifeq ($(UNAME), Linux)
# 	LIBX = minilibx/minilibx_linux/
# 	COMPILE = -L$(LIBX) -lmlx_Linux -L/usr/lib -I$(LIBX) -lXext -lX11 -lm -lz
# 	PREBUILD = xdpyinfo | awk '/dimensions/ {print $$2}' > resolution
# endif
# ifeq ($(UNAME), Darwin)
# 	LIBX = minilibx/minilibx_macos/
# 	COMPILE = -L$(LIBX) -lmlx -framework OpenGL -framework AppKit
# 	PREBUILD = system_profiler SPDisplaysDataType | awk '/Resolution/ {print $$2, $$3, $$4}' > resolution
# endif

# $(shell $(PREBUILD))

NAME		=	libminirt.a
FLAGS		=	-Wall -Wextra -Werror
OBJS_DIR	=	objects/
OBJS		=	$(addprefix $(OBJS_DIR), $(notdir $(SRC:.c=.o)))

# source files here #
SRC			=	error.c	\
				get_next_line.c \
				free.c \
				add_shapes.c \
				add_single.c \
				parse_helpers.c \
				parse.c \
				general_utils.c \
				parse_utils.c \
				test_parser.c \
				test_utils.c \

# source directory here #
SRC_DIR		=	$(LIBX)	\
				src	\
				src/mem_free \
				src/parsing \
				src/utils \
				src/tests \

vpath %.c $(SRC_DIR)

INCLUDES	=	-Ilibft -Iincludes

all:			$(NAME) minirt

test:	$(NAME) src//tests/test_main.c $(OBJS)
			gcc $(FLAGS) -g3 src/tests/test_main.c -L. -lminirt -Llibft -lft $(INCLUDES) -o test

$(NAME):		$(OBJS)
			@make -C libft/ all
			@ar rc $(NAME) $(OBJS)

$(OBJS_DIR)%.o:	%.c
			@mkdir -p $(OBJS_DIR)
			@echo "Compiling: $<"
			gcc $(FLAGS) $(INCLUDES) -c $< -o $@

minirt:		src/main.c $(OBJS)
			gcc $(FLAGS) -g3 src/main.c -L. -lminirt -Llibft -lft $(INCLUDES) $(COMPILE) -o minirt

clean:
			@make -C libft/ clean
			@rm -rf objects
			@rm -rf resolution
			@make -C libft/ clean
			@echo "Done!"

fclean:		clean
			@make -C libft/ fclean
			@rm -rf $(NAME) minirt
			@echo "Done!"

re:			fclean all

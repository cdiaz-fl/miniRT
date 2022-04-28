# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/22 09:42:42 by zcanales          #+#    #+#              #
#    Updated: 2022/04/26 09:16:17 by cdiaz-fl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRCS = src/maths/point_vect_operations.c\
	   src/maths/vect_operations1.c\
	   src/maths/vect_operations2.c\
	   src/intersections/intersection.c\
	   src/mlx/mlx_utils.c\
	   src/mlx/mlx_event.c\
	   src/get_data/main_read.c\
	   src/get_data/get_next_line.c\
		 src/get_data/create_objects.c\
		 src/get_data/spheres.c\
		 src/get_data/planes.c\
		 src/get_data/cylinders.c\
	   src/errors/error_handling.c\
		 #src/intersections/inter_lst.c\#
	   #src/main_prueba.c\

OBJS = $(SRCS:.c=.o)

INCLUDES = includes/

MAKE = make
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

MLX_A = lib/mlx/libmlx.a
LIB_A = lib/libft/libft.a

CC = gcc
#CFLAGS = -Wall -Wextra -Werror
SEG_FLAGS = -g3 -fsanitize=address
MLX_FLAGS = -L./lib/mlx -framework OpenGL -framework AppKit $(SEG_FLAGS) #-lmlx 

all: $(NAME)

$(NAME): $(OBJS) $(LIB_A) $(MLX_A) 
	@$(CC) $(CFLAGS) -I$(INCLUDES) $(MLX_FLAGS) $^ -o $(NAME)
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

%.o: %.c 
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(LIB_A) : lib/Libft/*.c lib/Libft/libft.h
	@$(MAKE) -C lib/libft/ bonus
	 @echo "$(NAME): $(GREEN)Creating $(LIB_A)...$(RESET)"

$(MLX_A) :
	@$(MAKE) -C lib/mlx/
	@echo "$(NAME): $(GREEN)Creating $(MLX_A)...$(RESET)"

clean :
	make -C lib/libft/ clean
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean : clean
	make -C lib/libft/ fclean
	make -C lib/mlx/ clean
	@echo "$(NAME): $(RED)$(LIB_A) was deleted$(RESET)"
	@rm -rf $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY : re all fclean clean


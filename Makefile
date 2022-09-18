# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cleticia <cleticia@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/23 01:32:02 by cleticia          #+#    #+#              #
#    Updated: 2021/10/22 04:32:49 by cleticia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
RM = rm -rf
FLAGS = -Wall -Werror -Wextra
MLX = mlx/libmlx.a
LFT = libft/libft.a
INC = -I ./inc -I ./libft -I ./mlx -I ./inc
LIB = -L ./libft -lft -L ./mlx -lmlx -lXext -lX11 -lm -lbsd
OBJ = $(SRC:.c=.o)
SRC = ./src/main.c\
	./src/so_long.c\
	./src/paint_map.c\
	./src/event_key.c\
	./src/parsing_map.c\
	./src/verif_map.c\
	./src/get_next_line.c\
	./src/get_next_line_utils.c\

all: $(MLX) $(LFT) $(NAME)

install:
	@sudo apt-get install gcc make xorg libxext-dev libbsd-dev

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^ $(LIB)

$(MLX):
	@echo "Compiling minilibx"
	@make -s -C mlx
	@echo "Minilibx compiled!"

$(LFT):
	@echo "Compiling libft"
	@make -s -C libft
	@echo "Libft ready!"

.c.o:
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

clean:
	@make -s $@ -C libft
	$(RM) $(OBJ)
	@echo "OBJECT deleted"

fclean: clean
	@make -s $@ -C libft
	@make -s clean -C mlx
	@$(RM) $(NAME)
	@echo "Binary files deleted"

re: fclean all

.PHONY: all clean fclean re

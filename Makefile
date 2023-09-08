# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avon-ben <avon-ben@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 18:03:37 by jbax              #+#    #+#              #
#    Updated: 2023/09/08 16:41:50 by avon-ben         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH= expander : executor : files : lexer : headers : nextline

NAME= cub3D

SRC= main.c color.c map.c map_checks.c map_errors.c minimap.c \
	rotation.c drawing.c temp_tools.c tools.c mmap_init.c \
	rays.c
SRC+= background.c map_png.c
SRC+= get_next_line.c get_next_line_utils.c

OBF_DIR= OBF

OBF= $(SRC:%.c=$(OBF_DIR)/%.o)

# HEADER= ./mlx/include

HEADER+= get_next_line.h color.h map.h defines.h 

lib=libft/libft.a

MLX=mlx/build/libmlx42.a
MLXINC= -Iinclude -lglfw -lm\
		# -framework Cocoa -framework OpenGL -framework IOKit

CC= gcc

CFLAGS+= -g 
CFLAGS+= -Wall -Wextra -Werror
CFLAGS+= $(SAN)
# CFLAGS+= --coverage
CFLAGS+= -o

# RLINE= -lreadline -L ~/.brew/opt/readline/lib/ $(lib)

SAN= -fsanitize=address

OO= -O3

all:
	@$(MAKE) $(NAME) -j

$(NAME): $(OBF_DIR) $(OBF) 
	$(CC) $(CFLAGS) $@ $(OBF) $(RLINE) $(lib) $(MLX) $(MLXINC)

$(OBF_DIR)/%o: %c $(HEADER) $(lib)
	$(CC) -c $(CFLAGS) $@ $< -I ~/.brew/opt/readline/include/

$(lib):
	$(MAKE) -C libft bonus

# $(MLX):
# 	@ $(MAKE) -C $(MLXDIR) 

tt:
	bash get_mlx.sh

$(OBF_DIR):
	mkdir $(OBF_DIR)

clean:
	@rm -rf $(OBF) $(OBF_DIR)

fclean:
	@rm -rf $(OBF) $(OBF_DIR) $(NAME)
	$(MAKE) -C libft fclean

f: fclean

r:$(NAME)
	# ./$(NAME) map/example.cu
	# ./$(NAME) map/example.cub.txt
	# ./$(NAME) map/example.c
	# ./$(NAME) map/example.cub.cub
	# ./$(NAME) map/example.cub
	./$(NAME) map/test.cub
re:
	@$(MAKE) fclean
	@$(MAKE) all

norm: $(SRC) $(HEADER)
	norminette $^

.PHONY: all re fclean clean f norm r

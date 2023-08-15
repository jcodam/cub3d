# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbax <jbax@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2023/01/17 18:03:37 by jbax          #+#    #+#                  #
#    Updated: 2023/08/13 20:12:14 by avon-ben      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH= expander : executor : files : lexer : headers : nextline

NAME= cub3D

SRC= main.c color.c map.c map_checks.c map_errors.c minimap.c minimap_tools.c \
	rotation.c make_base_minimap.c drawing.c temp_tools.c tools.c mmap_init.c \
	rays.c
SRC+=  
SRC+= get_next_line.c get_next_line_utils.c

OBF_DIR= OBF

OBF= $(SRC:%.c=$(OBF_DIR)/%.o)

HEADER= ./mlx/include

HEADER+= get_next_line.h color.h map.h defines.h 

lib=libft/libft.a

MLX=mlx/build/libmlx42.a
MLXINC= -Iinclude -lglfw3 \
		-framework Cocoa -framework OpenGL -framework IOKit

CC= gcc

CFLAGS= -g -Wall -Wextra -Werror
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
	$(CC) -c $(CFLAGS) $@ $< -I ~/.brew/opt/readline/include/ -I $(lib)

$(lib):
	$(MAKE) -C libft bonus

# $(MLX):
# 	@ $(MAKE) -C $(MLXDIR)

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
	./$(NAME) map/example.cub
re:
	@$(MAKE) fclean
	@$(MAKE) all

norm: $(SRC) $(HEADER)
	norminette $^

.PHONY: all re fclean clean f norm r

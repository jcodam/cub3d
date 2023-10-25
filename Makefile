# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbax <jbax@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 18:03:37 by jbax              #+#    #+#              #
#    Updated: 2023/10/25 19:31:11 by jbax             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

VPATH= nextline

NAME= cub3D

SRC= main.c color.c map.c map_checks.c map_errors.c minimap.c \
	drawing.c tools.c mmap_init.c rays_directions.c \
	rays.c map_tiles.c movement.c minimap_tools.c rays_tools.c
SRC+= background.c map_png.c put_textures.c
SRC+= get_next_line.c get_next_line_utils.c

OBF_DIR= OBF

OBF= $(SRC:%.c=$(OBF_DIR)/%.o)

# HEADER= ./mlx/include

HEADER+= get_next_line.h color.h map.h defines.h 

lib=libft/libft.a

MLX=mlx/build/libmlx42.a
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
CCFLAGS += -D LINUX
MLXINC= -Iinclude -lglfw -lm
endif
ifeq ($(UNAME_S),Darwin)
CCFLAGS += -D OSX
MLXINC= -Iinclude -lglfw3 -lm \
		-framework Cocoa -framework OpenGL -framework IOKit
endif

CC= gcc

CFLAGS+= -Wall -Wextra -Werror
ifdef S
CFLAGS+= -g 
CFLAGS+= $(SAN)
endif

# CFLAGS+= --coverage
CFLAGS+= -o

# RLINE= -lreadline -L ~/.brew/opt/readline/lib/ $(lib)
SAN+= -fsanitize=address
# SAN+= -fsanitize=leak

OO= -O3

all:
	@$(MAKE) mlx --no-print-directory
	@$(MAKE) $(NAME) -j --no-print-directory

$(NAME): $(OBF_DIR) $(OBF)
	$(CC) $(CFLAGS) $@ $(OBF) $(RLINE) $(lib) $(MLX) $(MLXINC)

$(OBF_DIR)/%o: %c $(HEADER) $(lib)
	$(CC) -c $(CFLAGS) $@ $< -I ~/.brew/opt/readline/include/

$(lib):
	$(MAKE) -C libft bonus

# $(MLX):
# 	@ $(MAKE) -C $(MLXDIR) 

mlx:
	@bash get_mlx.sh --no-print-directory

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
	# ./$(NAME) map/bigmap.cub
	# ./$(NAME) map/smallmap.cub
	# ./$(NAME) map/smallishmap.cub
	# ./$(NAME) map/NotAsBigmap.cub
re:
	@$(MAKE) fclean
	@$(MAKE) all

norm: $(SRC) $(HEADER)
	norminette $^

.PHONY: all re fclean clean f norm r mlx

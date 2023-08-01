# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbax <jbax@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2023/01/17 18:03:37 by jbax          #+#    #+#                  #
#    Updated: 2023/08/01 16:51:22 by jbax          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH= expander : executor : files : lexer : headers : nextline

NAME= cub3D

SRC= main.c color.c map.c map_checks.c map_errors.c
SRC+=  
SRC+= get_next_line.c get_next_line_utils.c

OBF_DIR= OBF

OBF= $(SRC:%.c=$(OBF_DIR)/%.o)

HEADER= 

HEADER+= get_next_line.h color.h map.h

lib=libft/libft.a

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
	$(CC) $(CFLAGS) $@ $(OBF) $(RLINE) $(lib)

$(OBF_DIR)/%o: %c $(HEADER) $(lib)
	$(CC) -c $(CFLAGS) $@ $< -I ~/.brew/opt/readline/include/ -I $(lib)

$(lib):
	$(MAKE) -C libft bonus

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

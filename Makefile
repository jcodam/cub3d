# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jbax <jbax@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2023/01/17 18:03:37 by jbax          #+#    #+#                  #
#    Updated: 2023/07/11 17:29:34 by jbax          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

VPATH= expander : executor : files : lexer : headers : parser

NAME= cub3D

SRC= 
SRC+= 

OBF_DIR= OBF

OBF= $(SRC:%.c=$(OBF_DIR)/%.o)

HEADER= 

lib=libft/libft.a

CC= gcc

CFLAGS= -g -Wall -Wextra -Werror
# CFLAGS+= $(SAN)
# CFLAGS+= --coverage
CFLAGS+= -o

# RLINE= -lreadline -L ~/.brew/opt/readline/lib/ $(lib)

SAN= -fsanitize=address

OO= -O3

all:
	@$(MAKE) $(NAME) -j

$(NAME): $(OBF_DIR) $(OBF)
	$(CC) $(CFLAGS) $@ $(OBF) $(RLINE) 

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
	./$(NAME)
re:
	@$(MAKE) fclean
	@$(MAKE) all

norm: $(SRC) $(HEADER)
	norminette $^

.PHONY: all re fclean clean f norm

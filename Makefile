# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wta <wta@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 20:09:26 by wta               #+#    #+#              #
#    Updated: 2020/02/01 11:15:11 by wta              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nm
CFLAGS = -Wall -Wextra -Werror# -g3 -fsanitize=address
CC = cc -O2

INC_DIR = include
OBJ_DIR = objs
SRCS_DIR =	src
LIBFT = libft

HEADERS =	\
nm.h

SRCS =					\
core/format.c			\
core/header.c			\
core/list.c				\
core/load_commands.c	\
core/magic.c			\
core/sections.c			\
core/symbol.c			\
utils/spec.c			\
utils/swap_bytes.c		\
main.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/, $(OBJ))
	$(MAKE) -j10 -C libft
	$(CC) $(CFLAGS) $^ -L $(LIBFT) -lft -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/utils
	mkdir -p $(OBJ_DIR)/core

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(addprefix $(INC_DIR)/, $(HEADERS)) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(addprefix $(LIBFT)/, $(INC_DIR)) -c -o $@ $<

clean:
	$(MAKE) -C libft clean
	/bin/rm -rf $(OBJ)
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all $(LIBFT) clean fclean re

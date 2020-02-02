# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wta <wta@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 20:09:26 by wta               #+#    #+#              #
#    Updated: 2020/02/02 18:35:55 by wta              ###   ########.fr        #
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

SRCS =							\
core/fat/handler.c				\
core/mach-o/format.c			\
core/mach-o/handler.c			\
core/mach-o/header.c			\
core/mach-o/list.c				\
core/mach-o/load_commands.c		\
core/mach-o/magic.c				\
core/mach-o/sections.c			\
core/mach-o/sort.c				\
core/mach-o/symbol.c			\
utils/compare.c					\
utils/pointer_check.c			\
utils/print.c					\
utils/spec.c					\
utils/swap_bytes.c				\
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
	mkdir -p $(OBJ_DIR)/core/fat
	mkdir -p $(OBJ_DIR)/core/mach-o

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

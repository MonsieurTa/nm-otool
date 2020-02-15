# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wta <wta@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 20:09:26 by wta               #+#    #+#              #
#    Updated: 2020/02/15 16:50:43 by wta              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nm_otool
FT_NM = ft_nm
FT_OTOOL = ft_otool
BIN1 = c_ft_nm
BIN2 = c_ft_otool
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CC = cc -O2

INC_DIR = include
OBJ_DIR = objs
SRCS_DIR =	src
LIBFT = libft

HEADERS =	\
ft_nm.h

NM_SRCS =										\
common/fat.c									\
core/fat/architecture/dispatchers/arm.c			\
core/fat/architecture/dispatchers/hppa.c		\
core/fat/architecture/dispatchers/i860.c		\
core/fat/architecture/dispatchers/mc680.c		\
core/fat/architecture/dispatchers/mc88000.c		\
core/fat/architecture/dispatchers/mc98000.c		\
core/fat/architecture/dispatchers/ppc.c			\
core/fat/architecture/dispatchers/sparc.c		\
core/fat/architecture/dispatchers/vax.c			\
core/fat/architecture/dispatchers/x86.c			\
core/fat/architecture/dispatcher.c				\
core/fat/handler.c								\
core/mach-o/format.c							\
core/mach-o/handler.c							\
core/mach-o/header.c							\
core/mach-o/list.c								\
core/mach-o/load_commands.c						\
core/mach-o/magic.c								\
core/mach-o/sections.c							\
core/mach-o/sort.c								\
core/mach-o/symbol.c							\
core/process.c									\
error/error.c									\
utils/compare.c									\
utils/pointer_check.c							\
utils/print.c									\
utils/spec.c									\
utils/swap_bytes.c								\
utils/swap_fat_arch.c							\
ft_nm.c											\

OTOOL_SRCS =									\
common/fat.c									\
core/mach-o/header.c							\
core/mach-o/magic.c								\
core/process.c									\
error/error.c									\
utils/pointer_check.c							\
utils/spec.c									\
utils/swap_bytes.c								\
utils/swap_fat_arch.c							\
ft_otool.c

NM_OBJ = $(NM_SRCS:.c=.o)
OTOOL_OBJ = $(OTOOL_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(FT_NM) $(FT_OTOOL)

$(LIBFT):
	$(MAKE) -j10 -C libft

$(FT_NM): $(addprefix $(OBJ_DIR)/, $(NM_OBJ))
	$(MAKE) -j10 -C libft
	$(CC) $(CFLAGS) -L $(LIBFT) -lft $^ -o $(FT_NM)

$(FT_OTOOL): $(addprefix $(OBJ_DIR)/, $(OTOOL_OBJ))
	$(MAKE) -j10 -C libft
	$(CC) $(CFLAGS) -L $(LIBFT) -lft $^ -o $(FT_OTOOL)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/common
	mkdir -p $(OBJ_DIR)/core
	mkdir -p $(OBJ_DIR)/core/fat
	mkdir -p $(OBJ_DIR)/core/fat/architecture
	mkdir -p $(OBJ_DIR)/core/fat/architecture/dispatchers
	mkdir -p $(OBJ_DIR)/core/mach-o
	mkdir -p $(OBJ_DIR)/error
	mkdir -p $(OBJ_DIR)/utils

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c $(addprefix $(INC_DIR)/, $(HEADERS)) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INC_DIR) -I $(addprefix $(LIBFT)/, $(INC_DIR)) -c -o $@ $<

libft_clean:
	$(MAKE) -C libft clean

libft_fclean:
	$(MAKE) -C libft fclean

clean: libft_clean
	/bin/rm -rf $(OBJ_DIR)

fclean: libft_fclean clean
	/bin/rm -f $(FT_NM) $(FT_OTOOL)

re: fclean all

.PHONY: all $(LIBFT) clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/15 14:23:26 by xlok              #+#    #+#              #
#    Updated: 2024/08/06 19:21:41 by xlok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Werror -Wextra

INC := ../../inc
INC_FLAG := -I$(INC)

DEP := $(INC)/ft_dprintf.h

SRC := ft_dprintf.c \
	   ft_dprintf_init.c \
	   ft_dprintf_parse.c \
	   ft_dprintf_fs_padding.c \
	   ft_dprintf_fs_putnbr.c \
	   ft_dprintf_fs_c.c \
	   ft_dprintf_fs_s.c \
	   ft_dprintf_fs_p.c \
	   ft_dprintf_fs_di.c \
	   ft_dprintf_fs_di_printnum.c \
	   ft_dprintf_fs_u.c \
	   ft_dprintf_fs_u_printnum.c \
	   ft_dprintf_fs_x.c \
	   ft_dprintf_fs_x_printnum.c

OBJ_DIR := ../../obj
OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

.PHONY: all $(OBJ_DIR) clean

all: $(OBJ)

$(OBJ_DIR)/%.o: %.c $(DEP)
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

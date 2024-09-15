#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xlok <xlok@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 19:32:42 by xlok              #+#    #+#              #
#    Updated: 2024/08/06 19:16:24 by xlok             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC := cc
CFLAGS := -Wall -Werror -Wextra

INC := ../../inc
INC_FLAG := -I$(INC)

DEP := $(INC)/gnl.h

SRC := gnl.c \
	   gnl_utils.c

OBJ_DIR := ../../obj
OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

.PHONY: all $(OBJ_DIR) clean

all: $(OBJ)

$(OBJ_DIR)/%.o: %.c $(DEP)
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

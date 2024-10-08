# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/11 13:33:12 by xlok              #+#    #+#              #
#    Updated: 2024/08/11 13:33:15 by xlok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAGS := -Wall -Werror -Wextra

INC := ../../inc
INC_FLAG := -I$(INC)

DEP := $(INC)/libft.h

SRC := ft_atoi.c \
	   ft_bzero.c \
	   ft_calloc.c \
	   ft_isalnum.c \
	   ft_isalpha.c \
	   ft_isascii.c \
	   ft_isdigit.c \
	   ft_isprint.c \
	   ft_itoa.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_memcpy.c \
	   ft_memmove.c \
	   ft_memset.c \
	   ft_putchar_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_putstr_fd.c \
	   ft_split.c \
	   ft_strchr.c \
	   ft_strdup.c \
	   ft_striteri.c \
	   ft_strjoin.c \
	   ft_strlcat.c \
	   ft_strlcpy.c \
	   ft_strlen.c \
	   ft_strmapi.c \
	   ft_strncmp.c \
	   ft_strnstr.c \
	   ft_strrchr.c \
	   ft_strtrim.c \
	   ft_substr.c \
	   ft_tolower.c \
	   ft_toupper.c \
	   ft_lstnew_bonus.c \
	   ft_lstadd_front_bonus.c \
	   ft_lstsize_bonus.c \
	   ft_lstlast_bonus.c \
	   ft_lstadd_back_bonus.c \
	   ft_lstdelone_bonus.c \
	   ft_lstclear_bonus.c \
	   ft_lstiter_bonus.c \
	   ft_lstmap_bonus.c \

OBJ_DIR := ../../obj
OBJ := $(addprefix $(OBJ_DIR)/,$(SRC:%.c=%.o))

.PHONY: all $(OBJ_DIR) clean

all: $(OBJ)

$(OBJ_DIR)/%.o: %.c $(DEP)
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

clean:
	rm -f $(OBJ)

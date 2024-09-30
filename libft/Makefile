# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: xlok <xlok@student.42singapore.sg>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 19:32:42 by xlok              #+#    #+#              #
#    Updated: 2024/10/08 00:22:16 by xlok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJ := libft-updated

NAME := libft.a 

CC := cc
CFLAGS := -Wall -Werror -Wextra -I.

FT := libft \
	  ft_dprintf \
	  gnl

OBJ_DIR := obj
OBJ := $(OBJ_DIR)/*.o

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(FT)
	ar rcs $@ $(OBJ)

$(FT):
	mkdir -p $(OBJ_DIR)
	$(MAKE) -C src/$@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

TIMESTAMP := $(shell date +%Y%m%d%H%M%S)

bak:
	$(MAKE) fclean
	mkdir -p ../bak
	tar -cf ../bak/$(PROJ).bak_$(TIMESTAMP).tar .

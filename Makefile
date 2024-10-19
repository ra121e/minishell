# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/15 14:23:26 by xlok              #+#    #+#              #
#    Updated: 2024/10/19 20:01:59 by athonda          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

BONUS_NAME := minishell_bonus

LIB_DIR := libft
LIB := $(LIB_DIR)/libft.a

CC := cc
INC_FLAG := -Iinc -I$(LIB_DIR)/inc
CFLAGS := -g -Wall -Werror -Wextra
LINK := -L$(LIB_DIR) -lft -lreadline

DEP := inc/minishell.h
BONUS_DEP := inc/minishell_bonus.h

SRC_DIR := src
SRC_F := minishell.c \
		 lexer.c \
		 lexer_helper.c \
		 builtin_pwd.c \
		 builtin_env.c \
		 builtin_export.c \
		 builtin_export_helper.c \
		 tokenize.c \
		 token.c \
		 parser.c \
		 parser_expr.c \
		 parser_pip.c \
		 parser_command.c \
		 parser_subshell.c \
		 parser_redirect.c \
		 parser_helper.c \
		 ast.c \
		 traverse.c \
		 exec_cmd.c \
		 get_fullpath.c \
		 free_split.c \
		 error.c

SRC := $(SRC_F:%.c=$(SRC_DIR)/%.c)

OBJ_DIR := obj
OBJ := $(SRC_F:%.c=$(OBJ_DIR)/%.o)

BONUS_SRC_DIR := bonus_src
BONUS_SRC_F :=	so_long_bonus.c \
				init_bonus.c \
				validate_map_bonus.c \
				validate_map_path_bonus.c \
				render_bonus.c \
				animate_bonus.c \
				movement_bonus.c \
		 		get_pos_bonus.c \
				handler_bonus.c \
				enemy_bonus.c \
				error_bonus.c

BONUS_SRC := $(BONUS_SRC_F:%.c=$(BONUS_SRC_DIR)/%.c)

BONUS_OBJ_DIR := bonus_obj
BONUS_OBJ := $(BONUS_SRC_F:%.c=$(BONUS_OBJ_DIR)/%.o)

.PHONY: all clean fclean re bonus norm

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINK) -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIB) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LINK) -o $@

$(LIB):
	$(MAKE) -C $(LIB_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c $(BONUS_DEP)
	@mkdir -p $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)

fclean: clean
	rm -rf $(NAME) $(BONUS_NAME) $(LIB)

re: fclean all

norm:
	clear
	@norminette $(SRC) $(BONUS_SRC) $(DEP) $(BONUS_DEP)

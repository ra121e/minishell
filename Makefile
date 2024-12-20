# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/15 14:23:26 by xlok              #+#    #+#              #
#    Updated: 2024/12/07 08:49:21 by xlok             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell

LIB_DIR := libft
LIB := $(LIB_DIR)/libft.a

CC := cc
INC_FLAG := -Iinc -I$(LIB_DIR)/inc
CFLAGS := -g -Wall -Werror -Wextra
LINK := -L$(LIB_DIR) -lft -lreadline

DEP := inc/minishell.h

SRC_DIR := src
SRC_F := minishell.c \
		 init.c \
		 init_shlvl.c \
		 cleanup.c \
		 free.c \
		 helper.c \
		 syntax_checker.c \
		 lexer.c \
		 expansion_var.c \
		 expansion_var_helper.c \
		 builtin.c \
		 builtin_echo.c \
		 builtin_cd.c \
		 builtin_pwd.c \
		 builtin_env.c \
		 builtin_export.c \
		 builtin_export_helper.c \
		 builtin_unset.c \
		 long_check.c \
		 builtin_exit.c \
		 tokenize.c \
		 token.c \
		 parser.c \
		 parser_expr.c \
		 parser_pip.c \
		 parser_command.c \
		 parser_subshell.c \
		 parser_redirect.c \
		 parser_helper.c \
		 error_parser.c \
		 ast.c \
		 traverse.c \
		 exec_cmd.c \
		 exec_cmd_helper.c \
		 exec_cmd_redirect.c \
		 exec_cmd_redirect_helper.c \
		 pipe_wait.c \
		 heredoc.c \
		 check_relative_path.c \
		 get_relative_path.c \
		 get_fullpath.c \
		 free_split.c \
		 error.c \
		 ft_strsjoin.c \
		 ft_m_atoi.c \
		 signal.c

SRC := $(SRC_F:%.c=$(SRC_DIR)/%.c)

OBJ_DIR := obj
OBJ := $(SRC_F:%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LINK) -o $@

$(LIB):
	$(MAKE) -C $(LIB_DIR) CFLAGS=$(CFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME) $(LIB)

re: fclean all

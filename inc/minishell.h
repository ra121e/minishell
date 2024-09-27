/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:34:03 by xlok              #+#    #+#             */
/*   Updated: 2024/09/27 19:32:27 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"

typedef enum e_token_kind t_token_kind;
enum e_token_kind
{
	TK_SINGLE_QUOTES,
	TK_WORD,
	TK_RESERVED,
	TK_BUILTIN,
	TK_NUM,
	TK_EOF,
};

typedef struct s_token t_token;
struct s_token
{
	t_token_kind	kind;
	t_token			*next;
	int				val;
	char			*str;
};

typedef struct s_ms
{
	int		start;
	int		end;
	int		len;
	char	*token;
}	t_ms;

int		is_space(char c);
t_token	*lexer(char *str);
char	*pwd(void);
t_token	*new_token(char *str,t_token_kind kind);
void	add_back(t_token **node, t_token *new);
t_token	*token_last(t_token *cur);
void	tokenize(t_token **head, char *p, t_token_kind kind);

#endif

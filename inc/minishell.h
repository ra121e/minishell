/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:34:03 by xlok              #+#    #+#             */
/*   Updated: 2024/10/09 21:07:25 by athonda          ###   ########.fr       */
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
	TK_REDIRECTION,
	TK_PIPE,
	TK_WORD,
	TK_AND,
	TK_OR,
	TK_LPAREN,
	TK_RPAREN,
	TK_PATHNAME,
	TK_RESERVED,
	TK_BUILTIN,
	TK_NUM,
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

typedef enum e_node_kind t_node_kind;
enum e_node_kind
{
	ND_PIPE,
	ND_COMMAND,
	ND_REDIRECT_IN,
	ND_REDIRECT_OUT,
	ND_REDIRECT_HEREDOC,
	ND_REDIRECT_APPEND,
	ND_SUBSHELL,
	ND_AND,
	ND_OR,
};

typedef struct s_node t_node;
struct s_node
{
	t_node_kind	kind;
	char		*str;
	char		*av;
	t_node		*left;
	t_node		*right;
	char		*red_symbol;
	char		*file_name;
	t_node		*next;
	t_token		*token;
};

t_token	*lexer(char *str);
bool	is_delimiter(char c);
bool	is_builtin(char *str);
char	*pwd(void);
t_token	*new_token(char *str,t_token_kind kind);
void	add_back(t_token **node, t_token *new);
t_token	*token_last(t_token *cur);
char	*token_kind(int k);
void	tokenize(t_token **head, char *p, t_token_kind kind);
void	lexer_quote(t_ms *ms, char *str, t_token **head);
void	lexer_redirection(t_ms *ms, char *str, t_token **head);
void	lexer_pipe(t_ms *ms, char *str, t_token **head);

t_node	*parse_expr(t_token *token);
t_node	*parse_pip(t_token *token);
t_node	*parse_command(t_token *token);
t_node	*parse_subshell(t_token *token);
t_node	*parse_redirect_re(t_token *token);
t_node	*parse_redirect(t_token *token);
t_node	*parse_command_re(t_token *token);
t_node	*parse_cmd(t_token *token);

t_token	*next_token(t_token *cur);
t_node	*ast_newnode(t_node_kind kind);
#endif

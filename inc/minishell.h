/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:34:03 by xlok              #+#    #+#             */
/*   Updated: 2024/10/13 17:29:29 by athonda          ###   ########.fr       */
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
	TK_AND,
	TK_OR,
	TK_PIPE,
	TK_REDIRECT_IN,
	TK_REDIRECT_OUT,
	TK_REDIRECT_HEREDOC,
	TK_REDIRECT_APPEND,
	TK_LPAREN,
	TK_RPAREN,
	TK_WILDCARD,
	TK_VAR,
	TK_VAR_QUOTE,
	TK_QUOTE,
	TK_WORD,
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

typedef struct s_envp t_envp;
struct s_envp
{
	char	*key;
	char	*value;
	char	*pair;
};

typedef struct s_ms
{
	t_envp	**envp;
	t_token	*head;
	char	*token;
	char	*key;
	char	*value;
	char	*pair;
	int		start;
	int		end;
	int		len;
	int		var_len;
	int		eq;
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
	ND_WORD,
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
void	lexer(t_ms *ms, char *str);
void	tokenize_word(t_ms *ms, char *str, int type);
void	tokenize_char(t_ms *ms, char *str);
bool	is_builtin(char *str);
char	*remove_quote(char *old);
t_token	*new_token(char *str, t_token_kind kind);
void	add_back(t_token **node, t_token *new);
t_token	*token_last(t_token *cur);
char	*token_kind(int k);
void	tokenize(t_ms *ms, t_token_kind kind);
void	lexer_quote(t_ms *ms, char *str);
void	lexer_parenthesis(t_ms *ms, char *str);
void	lexer_wildcard(t_ms *ms, char *str);
void	lexer_operator(t_ms *ms, char *str);
void	lexer_redirection(t_ms *ms, char *str);
void	lexer_var(t_ms *ms, char *str, int type);
char	*b_pwd(void);
void	init_env(t_ms *ms, char **envp);
void	b_env(t_envp **envp);
void	b_export(t_ms *ms, char *str);
void	b_export_add(t_ms *ms, t_envp **envp);
int		display_if_no_arg(t_ms *ms, char c);
void	export_add(t_ms *ms, t_envp **envp);
void	update_env(t_ms *ms);
int		get_var_len(t_ms *ms, char *var);
char	*getvar(t_ms *ms, char *var);

t_node	*parser(t_token **token);
t_node	*parser_expr(t_token **token);
t_node	*parser_pip(t_token **token);
t_node	*parser_command(t_token **token);
t_node	*parser_subshell(t_token **token);
t_node	*parser_redirect_re(t_token **token);
t_node	*parser_redirect_right(t_token **token);
t_node	*parser_redirect(t_token **token);
t_node	*parser_cmd_re(t_token **token);
t_node	*parser_cmd_right(t_token **token);
t_node	*parser_cmd(t_token **token);

t_token	*next_token(t_token *cur);
t_node	*ast_newnode(t_node_kind kind);
const char* getNodeKindName(t_node_kind kind);
void printAST(t_node *node, int level, int isLeft);
#endif

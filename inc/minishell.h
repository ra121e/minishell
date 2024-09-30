/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:34:03 by xlok              #+#    #+#             */
/*   Updated: 2024/10/11 08:04:14 by xlok             ###   ########.fr       */
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
	TK_LPAREN,
	TK_RPAREN,
	TK_PIPE,
	TK_REDIRECT_IN,
	TK_REDIRECT_OUT,
	TK_REDIRECT_HEREDOC,
	TK_REDIRECT_APPEND,
	TK_VAR,
	TK_VAR_QUOTE,
	TK_QUOTE,
	TK_WORD,
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
}	t_ms;

void	lexer(t_ms *ms, char *str);
void	lexer_word(t_ms *ms, char *str, int type);
void	lexer_single(t_ms *ms, char *str);
bool	is_builtin(char *str);
char	*remove_quote(char *old);
t_token	*new_token(char *str, t_token_kind kind);
void	add_back(t_token **node, t_token *new);
t_token	*token_last(t_token *cur);
char	*token_kind(int k);
void	tokenize(t_ms *ms, t_token_kind kind);
void	lexer_quote(t_ms *ms, char *str);
void	lexer_parenthesis(t_ms *ms, char *str);
void	lexer_operator(t_ms *ms, char *str);
void	lexer_redirection(t_ms *ms, char *str);
void	lexer_var(t_ms *ms, char *str, int type);
char	*b_pwd(void);
void	init_env(t_ms *ms, char **envp);
void	b_env(t_envp **envp);
void	b_export(t_ms *ms, char *str);
void	b_export_add(t_ms *ms, t_envp **envp);
int		get_var_len(t_ms *ms, char *var);
char	*getvar(t_ms *ms, char *var);

#endif

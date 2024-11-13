/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:34:03 by xlok              #+#    #+#             */
/*   Updated: 2024/11/13 22:06:23 by xlok             ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <signal.h>
# include <errno.h>
# include "libft.h"

# define READ O_RDONLY
# define WRITE 01101
//# define WRITE O_CREAT | O_WRONLY | O_TRUNC
# define APPEND 02101
//# define APPEND O_CREAT | O_WRONLY | O_APPEND
# define IS_REDIRECT > 100
# define HEREDOC 0
# define EXECUTE 1

extern int					g_sig;

typedef enum e_token_kind	t_token_kind;
enum e_token_kind
{
	TK_AND,
	TK_OR,
	TK_PIPE,
	TK_LPAREN,
	TK_RPAREN,
	TK_WORD,
	TK_EOF,
	TK_HEREDOC_DELIMITER,
	TK_REDIRECT_IN = 101,
	TK_REDIRECT_OUT,
	TK_REDIRECT_HEREDOC,
	TK_REDIRECT_APPEND,
};

typedef struct s_token		t_token;
struct s_token
{
	t_token_kind	kind;
	char			*str;
	t_token			*next;
};

typedef struct s_envp		t_envp;
struct s_envp
{
	char	*key;
	char	*value;
	char	*pair;
};

typedef enum e_node_kind	t_node_kind;
enum e_node_kind
{
	ND_PIPE,
	ND_COMMAND,
	ND_SUBSHELL,
	ND_AND,
	ND_OR,
	ND_WORD,
	ND_HEREDOC_DELIMITER,
	ND_REDIRECT_IN = 101,
	ND_REDIRECT_OUT,
	ND_REDIRECT_HEREDOC,
	ND_REDIRECT_APPEND,
};

typedef struct s_node		t_node;
struct s_node
{
	t_node_kind	kind;
	char		*str;
	char		*heredoc_str;
	t_node		*left;
	t_node		*right;
	bool		error;
};

typedef struct s_ms
{
	t_envp	**envp;
	t_token	*head;
	char	*prompt;
	char	*input;
	char	*token;
	char	*key;
	char	*value;
	char	*pair;
	char	*str;
	int		start;
	int		end;
	int		i;
	int		n;
	char	c;
	int		len;
	int		var_len;
	char	*var;
	char	*var_value;
	int		expand_var;
	char	*new_str;
	int		eq;
	bool	error;
	t_node	*start_node;
	char	*heredoc_filename;
	int		pipfd[2];
	int		fd_r;
	int		fd_w[2];
	int		builtin_cmd;
	int		pid;
	int		pid_status;
	int		in_pipe;
	char	**cmd;
	char	**cmd_envp;
	int		exit_status;
}	t_ms;

void	init(t_ms *ms, char **envp);
void	init_loop(t_ms *ms);
void	init_envp(t_ms *ms, char **envp);
void	cleanup(t_ms *ms);
int		syntax_checker(t_ms *ms, char *str);
void	lexer(t_ms *ms, char *str);
bool	is_builtin(char *str);
char	*ft_strsjoin(int count, ...);
char	*remove_quote(char *old);
t_token	*new_token(char *str, t_token_kind kind);
void	add_back(t_token **node, t_token *new);
t_token	*token_last(t_token *cur);
void	tokenize(t_ms *ms, t_token_kind kind);
void	tokenize_word(t_ms *ms, char *str, int type);
int		operator_char_count(char *str, int i);
void	tokenize_prior_str(t_ms *ms);

void	builtin(t_ms *ms);
void	builtin_echo(t_ms *ms);
void	builtin_cd(t_ms *ms);
void	builtin_pwd(t_ms *ms);
void	builtin_env(t_ms *ms);
void	builtin_export(t_ms *ms);
void	builtin_unset(t_ms *ms);
void	builtin_exit(t_ms *ms);
int		display_if_no_arg(t_ms *ms);
void	export_add(t_ms *ms, t_envp **envp);
void	update_env(t_ms *ms);
int		get_var_len(t_ms *ms, char *var);
char	*get_var(t_ms *ms, char *var);

void	ft_signal(void);
void	ft_signal_non(void);
void	ft_signal_heredoc(void);
void	ft_signal_cmd(void);

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
int		is_error_and_or(t_token *token);
int		is_error_eof(t_token *token);
int		is_error_pipe(t_token *token);
int		is_error_and_or_eof(t_token *token, t_node **node);
void	error_expr(t_token *token);
void	error_right(t_token *token);
void	error_pip(t_token *token);
void	error_subshell(t_token *token);

t_token	*next_token(t_token *cur);
t_node	*ast_newnode(t_node_kind kind);
void	ast_set_str_left(t_node *node, t_token **token, t_node *left);
void	traverse_start(t_node *head, t_ms *ms);
void	traverse(t_node *cur, t_ms *ms, int fd_w[2]);
void	heredoc(t_node *cur, char *delimiter);
int		heredoc_expand(t_ms *ms, t_node *node);
void	get_new_len(t_ms *ms, char *str, int i, int is_heredoc);
void	expand_var(t_ms *ms, char *str, int is_heredoc);
int		expand_var_found_var(t_ms *ms, char *str, int i, int quote);
void	expand_var_replace(t_ms *ms, int quote);
char	*remove_quote(char *old);
void	add_cmd_arg(t_ms *ms, char *str, int s, int i);
void	redirection(t_ms *ms, t_node *cur, int fd_w[2]);
void	exec_cmd(t_ms *ms);
void	exec_parent_wait(t_ms *ms);
void	init_cmd(t_ms *ms);
int		*init_fd_w(t_ms *ms);
void	dup2_and_close(pid_t old_fd, pid_t new_fd);
int		get_filename_fd(t_ms *ms, char *str, pid_t fd, int mode);
int		*exec_pip(t_ms *ms);
void	cmd_envp(t_ms *ms);
char	**find_envpath(t_ms *ms);
char	*join_cmd_path(char *cmd, char *path);
char	*get_fullpath(char *cmd, t_ms *ms);
void	free_split(char **str);
void	error_exit(char *str);
void	error_wrong_cmd(t_ms *ms);
void	error_malloc(t_ms *ms, char *msg);

void	free_str(char *str);
void	free_str_array(char **str);
void	free_token(t_ms *ms);
void	ast_free(t_node *node);
void	cleanup(t_ms *ms);
void	cleanup_envp(t_ms *ms);
void	cleanup_final(t_ms *ms);
void	close_fd(t_ms *ms);
#endif

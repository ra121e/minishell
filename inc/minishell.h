/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:34:03 by xlok              #+#    #+#             */
/*   Updated: 2024/10/30 08:28:58 by xlok             ###   ########.fr       */
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
# define WRITE O_CREAT | O_WRONLY | O_TRUNC
# define APPEND O_CREAT | O_WRONLY | O_APPEND
# define IS_REDIRECT > 100
# define INFO 0
# define EXECUTE 1 

typedef enum e_token_kind t_token_kind;
enum e_token_kind
{
	TK_AND,
	TK_OR,
	TK_PIPE,
	TK_HEREDOC_DELIMITER,
	TK_REDIRECT_IN,
	TK_REDIRECT_OUT,
	TK_REDIRECT_HEREDOC,
	TK_REDIRECT_APPEND,
	TK_LPAREN,
	TK_RPAREN,
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

typedef enum e_node_kind t_node_kind;
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

typedef struct s_node t_node;
struct s_node
{
	t_node_kind	kind;
	char		*str;
	char		**cmd;
	int			fd_r;
	int			fd_w[2];
	t_node		*left;
	t_node		*right;
	t_node		*next;
};

extern int	sig;

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
	t_node	*start_node;
	t_node	*tmp_node;
	t_node	*front;
	t_node	*back;
	int		heredoc_tmp;
	int		info;
	int		fd_r;
	int		fd_w[2];
	int		cmd_error;
	int		builtin_cmd;
	int		pid;
	t_node	*cmd_node;
	char	**cmd;
	char	**cmd_envp;
	int		exit_status;
	int		sig;
}	t_ms;

void	init(t_ms *ms);
void	init_envp(t_ms *ms, char **envp);
void	cleanup(t_ms *ms);
void	syntax_checker(char *str);
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
void	expansion(t_ms *ms, t_node *cur);
void	expansion_var(t_ms *ms, t_node *cur);
void	get_new_len(t_ms *ms, char *str, int i);
void	expand_var(t_ms *ms, char *str, int i);
int		expand_var_found_var(t_ms *ms, char *str, int i, int quote);
void	expand_var_replace(t_ms *ms, int quote);
char	*remove_quote(char *old);

void	builtin(t_ms *ms, t_node *cur);
void	builtin_echo(t_node *cur);
void	builtin_pwd(void);
void	builtin_env(t_ms *ms);
void	builtin_export(t_ms *ms);
void	builtin_export_add(t_ms *ms, t_envp **envp);
void	builtin_unset(t_ms *ms);
int		display_if_no_arg(t_ms *ms);
void	export_add(t_ms *ms, t_envp **envp);
void	update_env(t_ms *ms);
int		get_var_len(t_ms *ms, char *var);
char	*get_var(t_ms *ms, char *var);

void	ft_signal(void);
void	ft_signal_heredoc(void);
void	ft_signal_cmd(void);
void	ft_signal_int_ign(void);

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
void	error_expr(t_token *token);
void	error_right(t_token *token);
void	error_pip(t_token *token);
void	error_subshell(t_token *token);

t_token	*next_token(t_token *cur);
t_node	*ast_newnode(t_node_kind kind);
const char* getNodeKindName(t_node_kind kind);
void 	printAST(t_node *node, int level, int isLeft);
void	traverse_start(t_node *head, t_ms *ms, int action);
void	cmd_info(t_ms *ms, t_node *cur, int fd_w[2]);
void	exec_cmd(t_ms *ms, t_node *cur);
void	init_cmd(t_ms *ms, t_node *cur, int fd_w[2]);
void	heredoc(t_ms *ms, char *delimiter);
int		*init_fd_w(t_ms *ms);
void	dup2_and_close(pid_t old_fd, pid_t new_fd);
int		get_filename_fd(char *str, pid_t fd, int mode);
int		*exec_pip(t_ms *ms);
void	cmd_envp(t_ms *ms);
char	**find_envpath(t_ms *ms);
char	*join_cmd_path(char *cmd, char *path);
char	*get_fullpath(char *cmd, t_ms *ms);
void	free_split(char **str);
void	error_exit(char *str);
void	error_wrong_cmd(t_ms *ms);

void	cleanup(t_ms *ms);
void	cleanup_final(t_ms *ms);
void	close_fd(t_node *cur);
void	free_cmd(t_node *cur);
void	free_cmd_envp(char **cmd_envp);

void	print_token(t_ms *ms);
char	*token_kind(int k);
#endif

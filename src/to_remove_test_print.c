#include "minishell.h"

//For printing out during testing only; to remove before submission
void	print_token(t_ms *ms)
{
	if (ms->head)
	{
		printf("\033[32mtoken(s): \033[0m");
		while (ms->head)
		{
			printf("%s", ms->head->str);
			if (ms->head->next)
				printf("\033[32m -> \033[0m");
			ms->head = ms->head->next;
		}
		printf("\n");
	}
}

char	*token_kind(int k)
{
	if (k == TK_AND)
		return ("AND");
	else if (k == TK_OR)
		return ("OR");
	else if (k == TK_PIPE)
		return ("pipe");
	else if (k == TK_REDIRECT_IN)
		return ("redirect input");
	else if (k == TK_REDIRECT_OUT)
		return ("redirect output");
	else if (k == TK_REDIRECT_HEREDOC)
		return ("HEREDOC");
	else if (k == TK_REDIRECT_APPEND)
		return ("append output");
	else if (k == TK_LPAREN)
		return ("open parenthesis");
	else if (k == TK_RPAREN)
		return ("close parenthesis");
	else if (k == TK_WORD)
		return ("word");
	else if (k == TK_EOF)
		return ("EOF");
	return (0);
}

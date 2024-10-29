/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athonda <athonda@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:05:30 by athonda           #+#    #+#             */
/*   Updated: 2024/10/29 21:02:11 by xlok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ast_newnode(t_node_kind kind)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof (t_node) * 1);
	if (node == NULL)
		return (NULL);
	node->kind = kind;
	node->str = NULL;
	node->left = NULL;
	node->right = NULL;
	node->cmd = 0;
	node->fd_r = 0;
	node->fd_w[2] = 0;
	return (node);
}


// ノードの種類を文字列に変換する関数
const char* getNodeKindName(t_node_kind kind) {
    switch (kind) {
        case ND_PIPE: return "PIPE";
        case ND_COMMAND: return "COMMAND";
        case ND_REDIRECT_IN: return "REDIRECT_IN";
        case ND_REDIRECT_OUT: return "REDIRECT_OUT";
        case ND_REDIRECT_HEREDOC: return "REDIRECT_HEREDOC";
        case ND_REDIRECT_APPEND: return "REDIRECT_APPEND";
        case ND_SUBSHELL: return "SUBSHELL";
        case ND_AND: return "AND";
        case ND_OR: return "OR";
        case ND_WORD: return "WORD";
        default: return "UNKNOWN";
    }
}

// ASTを再帰的に表示する関数
void printAST(t_node *node, int level, int isLeft) {
    if (node == NULL) {
        return;
    }

    // インデントの設定
    int i = 0;
    while (i < level - 1) {
        printf("    ");
        i++;
    }

    // ノードの種類を表示（左か右かの表示も含む）
    if (level > 0) {
        if (isLeft) {
            printf("├── (right) ");  // 左のノードに対する表示
        } else {
            printf("└── (left) "); // 右のノードに対する表示
        }
    }

    // ノードの種類と追加情報を表示
    printf("Node Kind: %s", getNodeKindName(node->kind));
    if (node->str) {
        printf(", Str: %s", node->str);
    }
    printf("\n\n");

    // 左の子ノードを再帰的に表示
    printAST(node->right, level + 1, 1);

    // 右の子ノードを再帰的に表示
    printAST(node->left, level + 1, 0);

}

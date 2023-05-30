/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:32:27 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/29 10:06:16 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

#include "typedef.h"

#include <libft.h>

t_ast_node	*ast_node_new(t_ast_node_type type, t_ast_data data)
{
	t_ast_node *const	empty = malloc(sizeof(*empty));

	empty->type = type;
	empty->data = data;
	return (empty);
}

void	ast_node_del(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == AST_PIPE || node->type == AST_COMMAND)
	{
		ast_node_del(node->data.branch.left);
		ast_node_del(node->data.branch.right);
	}
	if (node->type == AST_ARGS)
		ft_strarr_del(node->data.args.argv);
	if (node->type == AST_REDIR)
		redir_del(node->data.redir.array, node->data.redir.size);
	free(node);
}

t_ast_node	*ast_left(t_ast_node *node)
{
	if (node->type == AST_ARGS || node->type == AST_REDIR)
	{
		return (NULL);
	}
	return (node->data.branch.left);
}

t_ast_node	*ast_right(t_ast_node *node)
{
	if (node->type == AST_ARGS || node->type == AST_REDIR)
	{
		return (NULL);
	}
	return (node->data.branch.right);
}

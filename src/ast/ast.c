/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:32:27 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/02 09:56:00 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

#include "typedef.h"

#include <libft.h>

t_ast_node	*ast_node_new(e_ast_node_type type, u_ast_data data)
{
	t_ast_node	*const empty = malloc(sizeof(*empty));
	
	*empty = (t_ast_node){type, data};
	return (empty);
}

void	ast_node_del(t_ast_node *node)
{
	if (node->type == AST_PIPE || node->type == AST_COMMAND)
	{
		if (node->data.branch.left)
			ast_node_del(node->data.branch.left);
		if (node->data.branch.right)
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

void	ast_print(t_ast_node *node, int depth)
{
	int i;

	i = 0;
	while (i++ < depth)
		ft_printf(" ");
	++depth;
	if (!node)
		ft_printf("NULL\n");
	else if (node->type == AST_PIPE)
	{
		ft_printf("PIPE\n");
		ast_print(node->data.branch.left, depth + 1);
		ast_print(node->data.branch.right, depth + 1);
	}
	else if (node->type == AST_COMMAND)
	{
		ft_printf("COMMAND\n");
		ast_print(node->data.branch.left, depth + 1);
		ast_print(node->data.branch.right, depth + 1);
	}
	else if (node->type == AST_ARGS)
	{
		ft_printf("ARGS %d\n", node->data.args.argc);
		char **it = node->data.args.argv;
		while (*it)
		{
			i = 0;
			while (i++ < depth)
				ft_printf(" ");
			ft_printf("\"%s\"\n", *it);
			++it;
		}
	}
	else if (node->type == AST_REDIR)
	{
		ft_printf("REDIR %d\n", node->data.redir.size);
		t_redir *it = node->data.redir.array;
		t_redir *end = it + node->data.redir.size;
		while (it != end)
		{
			i = 0;
			while (i++ < depth)
				ft_printf(" ");
			if (it->operation == REDIR_OUT_TRUNC)
				ft_printf("REDIR_OUT_TRUNC %d \"%s\"\n", it->file_descriptor, it->argument);
			else if (it->operation == REDIR_OUT_APPEND)
				ft_printf("REDIR_OUT_APPEND %d \"%s\"\n", it->file_descriptor, it->argument);
			else if (it->operation == REDIR_IN_FILE)
				ft_printf("REDIR_IN_FILE %d \"%s\"\n", it->file_descriptor, it->argument);
			else if (it->operation == REDIR_IN_HEREDOC)
				ft_printf("REDIR_IN_HEREDOC %d \"%s\"\n", it->file_descriptor, it->argument);
			else
				ft_printf("UNKNOWN");
			++it;
		}
	}
}

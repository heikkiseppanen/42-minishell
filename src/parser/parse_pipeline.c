/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:49:46 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/30 14:52:08 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

#include "tokenizer.h"

t_ast_node	*parse_pipeline(t_token **iterator)
{
	t_ast_node		*pipe;
	t_ast_branch	node_data;

	node_data.left = parse_command(iterator);
	if (!node_data.left || !token_is(*iterator, TOK_PIPE))
	{
		return (node_data.left);
	}
	*iterator += 1;
	node_data.right = parse_pipeline(iterator);
	if (!node_data.right)
	{
		ast_node_del(node_data.left);
		return (NULL);
	}
	pipe = ast_node_new(AST_PIPE, (t_ast_data)node_data);
	if (!pipe)
	{
		ast_node_del(node_data.left);
		ast_node_del(node_data.right);
	}
	return (pipe);
}

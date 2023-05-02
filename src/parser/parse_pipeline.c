/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:49:46 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/02 09:49:52 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast_node *parse_pipeline(t_lexer *input)
{
	t_ast_branch	node_data;

	node_data.left = parse_command(input);
	if (!node_data.left)
	{
		return (NULL);
	}
	if (lexer_next_is(input, TOK_EOF))
	{
		return (node_data.left);
	}
	if (!lexer_next_is(input, TOK_PIPE))
	{
		return (NULL);
	}
	lexer_parse_token(input);
	node_data.right = parse_pipeline(input);
	if (!node_data.right)
	{
		return (NULL);
	}
	return (ast_node_new(AST_PIPE, (u_ast_data)node_data));
}

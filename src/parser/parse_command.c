/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:47:14 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/04 19:47:45 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

#include "typedef.h"

static t_ast_node	*create_args_node(t_buf *argv)
{
	t_ast_args	node_data;
	t_ast_node	*arguments;

	if (!argv->size)
	{
		buf_del(argv);
		node_data.argc = 0;
		node_data.argv = NULL;
	}
	else
	{
		if (!buf_resize(argv, argv->size + 1))
			return (NULL);
		node_data.argc = argv->size;
		node_data.argv = argv->data;
		node_data.argv[node_data.argc] = NULL;
	}
	arguments = ast_node_new(AST_ARGS, (u_ast_data)node_data);
	if (!arguments)
	{
		ft_strarr_del(node_data.argv);
	}
	return (arguments);
}

static t_ast_node	*create_redir_node(t_buf *redir)
{
	t_ast_redir	node_data;
	t_ast_node	*redirections;

	if (!redir->size)
	{
		buf_del(redir);
		node_data.size = 0;
		node_data.array = NULL;
	}
	else
	{
		if (!buf_resize(redir, redir->size))
		{
			buf_del(redir);
			return (NULL);
		}
		node_data.size = redir->size;
		node_data.array = redir->data;
	}
	redirections = ast_node_new(AST_REDIR, (u_ast_data)node_data);
	if (!redirections)
	{
		redir_del(node_data.array, node_data.size);
	}
	return (redirections);
}

t_ast_node	*parse_command(t_token **iterator)
{
	t_buf			argv;
	t_buf			redir;
	t_ast_branch	node_data;
	t_ast_node		*command;

	if (!(buf_init(&argv, AST_INITIAL_ARGC, sizeof(char *))
		& buf_init(&redir, AST_INITIAL_ARGC, sizeof(t_redir)))
		|| !parse_parameters(iterator, &argv, &redir))
	{
		buf_del(&argv);
		buf_del(&redir);
		return (NULL);
	}
	node_data.left = create_args_node(&argv);
	node_data.right = create_redir_node(&redir);
	command = ast_node_new(AST_COMMAND, (u_ast_data)node_data);
	if (!command)
	{
		ast_node_del(node_data.left);
		ast_node_del(node_data.right);
	}
	return (command);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 10:32:27 by hseppane          #+#    #+#             */
/*   Updated: 2023/04/28 15:46:39 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

#include "typedef.h"

#include <stdio.h>

static e_err	parse_arg(t_lexer *input, t_buf *argv_out)
{
	const char	*argument;

	argument = token_to_str(&input->token);
	if (!buf_pushback(argv_out, &argument, 1))
		return (MS_FAIL);
	return (MS_SUCCESS);
}

static e_err	parse_redir(t_lexer *input, t_buf *redir_out)
{
	t_redir	redirection;

	if (lexer_next_is(input, TOK_GREAT | TOK_DGREAT))
		redirection.file_descriptor = STDOUT_FILENO;
	else if (lexer_next_is(input, TOK_LESS | TOK_DLESS))
		redirection.file_descriptor = STDIN_FILENO;
	else if (lexer_next_is(input, TOK_IO_NUMBER))
	{
		redirection.file_descriptor = ft_atoi(input->token.begin);
		lexer_parse_token(input);
	}
	else
		return (MS_FAIL);

	if (lexer_next_is(input, TOK_GREAT))
		redirection.operation = REDIR_OUT_TRUNC;
	else if (lexer_next_is(input, TOK_DGREAT))
		redirection.operation = REDIR_OUT_APPEND;
	else if (lexer_next_is(input, TOK_LESS))
		redirection.operation = REDIR_IN_FILE;
	else if (lexer_next_is(input, TOK_DLESS))
		redirection.operation = REDIR_IN_HEREDOC;
	else
		return (MS_FAIL);

	lexer_parse_token(input);

	if (lexer_next_is(input, TOK_WORD))
		redirection.argument = token_to_str(&input->token);
	else
		return (MS_FAIL);

	if (!buf_pushback(redir_out, &redirection, 1))
		return (MS_FAIL);
	return (MS_SUCCESS);
}

e_err parse_param(t_lexer *input, t_buf *argv_out, t_buf *redir_out)
{
	e_token_type	redir_token;
	e_err			status;

	redir_token = TOK_DLESS | TOK_LESS | TOK_DGREAT | TOK_GREAT | TOK_IO_NUMBER;
	status = MS_SUCCESS;
	while (status == MS_SUCCESS)
	{
		if (lexer_next_is(input, TOK_WORD))
			status = parse_arg(input, argv_out);
		else if (lexer_next_is(input, redir_token))
			status = parse_redir(input, redir_out);
		else
			return (MS_SUCCESS);
		lexer_parse_token(input);
	}
	return (MS_FAIL);
}

static t_ast_node	*create_args_node(t_buf *argv)
{
	t_ast_args	node_data;

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
	return (ast_node_new(AST_ARGS, (u_ast_data)node_data));
}

static t_ast_node	*create_redir_node(t_buf *redir)
{
	t_ast_redir	node_data;

	if (!redir->size)
	{
		buf_del(redir);
		node_data.size = 0;
		node_data.array = NULL;
	}
	else
	{
		if (!buf_resize(redir, redir->size))
			return (NULL);
		node_data.size = redir->size;
		node_data.array = redir->data;
	}
	return (ast_node_new(AST_REDIR, (u_ast_data)node_data));
}

t_ast_node	*parse_command(t_lexer *input)
{
	t_buf			argv;
	t_buf			redir;
	t_ast_branch	node_data;

	if (!lexer_next_is(input, TOK_WORD | TOK_IO_NUMBER))
		return (NULL);
	if (!(buf_init(&argv, AST_INITIAL_ARGC, sizeof(char *))
		& buf_init(&redir, AST_INITIAL_ARGC, sizeof(t_redir)))
		|| !parse_param(input, &argv, &redir))
	{
		buf_del(&argv);
		buf_del(&redir);
		return (NULL);
	}
	node_data.left = create_args_node(&argv);
	node_data.right = create_redir_node(&redir);
	return (ast_node_new(AST_COMMAND, (u_ast_data)node_data));
}

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

void	ast_print(t_ast_node *node, int depth)
{
	int i;

	i = 0;
	while (i++ < depth)
		printf(" ");
	++depth;
	if (!node)
		printf("NULL\n");
	else if (node->type == AST_PIPE)
	{
		printf("PIPE\n");
		ast_print(node->data.branch.left, depth + 1);
		ast_print(node->data.branch.right, depth + 1);
	}
	else if (node->type == AST_COMMAND)
	{
		printf("COMMAND\n");
		ast_print(node->data.branch.left, depth + 1);
		ast_print(node->data.branch.right, depth + 1);
	}
	else if (node->type == AST_ARGS)
	{
		printf("ARGS %d\n", node->data.args.argc);
		char **it = node->data.args.argv;
		while (*it)
		{
			i = 0;
			while (i++ < depth)
				printf(" ");
			printf("\"%s\"\n", *it);
			++it;
		}
	}
	else if (node->type == AST_REDIR)
	{
		printf("REDIR %d\n", node->data.redir.size);
		t_redir *it = node->data.redir.array;
		t_redir *end = it + node->data.redir.size;
		while (it != end)
		{
			i = 0;
			while (i++ < depth)
				printf(" ");
			if (it->operation == REDIR_OUT_TRUNC)
				printf("REDIR_OUT_TRUNC %d \"%s\"\n", it->file_descriptor, it->argument);
			else if (it->operation == REDIR_OUT_APPEND)
				printf("REDIR_OUT_APPEND %d \"%s\"\n", it->file_descriptor, it->argument);
			else if (it->operation == REDIR_IN_FILE)
				printf("REDIR_IN_FILE %d \"%s\"\n", it->file_descriptor, it->argument);
			else if (it->operation == REDIR_IN_HEREDOC)
				printf("REDIR_IN_HEREDOC %d \"%s\"\n", it->file_descriptor, it->argument);
			else
				printf("UNKNOWN");
			++it;
		}
	}
}

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

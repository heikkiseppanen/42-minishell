/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:38:53 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/04 19:41:43 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "tokenizer.h"
#include "ast.h"

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

e_err	handle_input(const char *input)
{
	t_token	*const	tokenized_input = tokenize_string(input);
	t_token		*token_iterator;
	t_ast_node	*syntax_tree;
	e_err		status;

	if (!tokenized_input)
		return (MS_FAIL);
	token_iterator = tokenized_input;
	syntax_tree = parse_pipeline(&token_iterator);
	free(tokenized_input);
	if (!syntax_tree)
		return (MS_FAIL);
	ast_print(syntax_tree, 0);
	status = interpret_ast(syntax_tree);
	ast_node_del(syntax_tree);
	return (status);
}

int	main(void)
{
	char	*input;

	rl_bind_key('\t', rl_complete);
	using_history();
	init_sighandler();
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		handle_input(input);
		add_history(input);
		free(input);
	}
	return (0);
}

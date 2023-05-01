/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:38:53 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/01 09:11:29 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "sig.h"

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

e_err	handle_input(const char *input)
{
	t_lexer		tokenizer;
	t_ast_node	*syntax_tree;
	e_err		status;

	tokenizer = lexer_new(input);
	syntax_tree = parse_pipeline(&tokenizer);
	if (!syntax_tree)
		return (MS_FAIL);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:38:53 by hseppane          #+#    #+#             */
/*   Updated: 2023/06/05 11:19:28 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft/htable.h"
#include "sig.h"
#include "tokenizer.h"
#include "ast.h"
#include "libft.h"
#include "sig.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

static t_err	handle_input(const char *input)
{
	t_token *const	tokenized_input = tokenize_string(input);
	t_token			*token_iterator;
	t_ast_node		*syntax_tree;
	t_err			status;

	if (!tokenized_input)
		return (MS_FAIL);
	token_iterator = tokenized_input;
	syntax_tree = parse_pipeline(&token_iterator);
	free(tokenized_input);
	if (!syntax_tree)
		return (MS_FAIL);
	status = interpret_ast(syntax_tree);
	ast_node_del(syntax_tree);
	return (status);
}

static void	shell_repl(struct termios *term)
{
	char	*input;

	tcgetattr(STDIN_FILENO, term);
	while (1)
	{
		register_handler(HANDLER_SH);
		term->c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, term);
		input = readline("> ");
		term->c_lflag |= ECHOCTL;
		tcsetattr(0, TCSANOW, term);
		if (!input)
			break ;
		handle_input(input);
		if (ft_strncmp("", input, 1))
			add_history(input);
		free(input);
	}
}

int	main(void)
{
	extern t_shell_state	g_state;
	struct termios			term;

	tcgetattr(STDIN_FILENO, &term);
	if (!ms_init())
	{
		exit (1);
	}
	shell_repl(&term);
	write(1, "exit\n", 5);
	ft_htable_destroy(g_state.envp, 1);
	exit (g_state.pipeline_err);
	return (0);
}

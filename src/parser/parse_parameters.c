/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:00:33 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/02 13:20:43 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static e_err	parse_argument(t_lexer *input, t_buf *argv_out)
{
	const char	*argument;

	argument = token_to_str(&input->token);
	if (!buf_pushback(argv_out, &argument, 1))
		return (MS_FAIL);
	return (MS_SUCCESS);
}

static e_err	parse_redirection(t_lexer *input, t_buf *redir_out)
{
	t_redir	redirection;

	if (lexer_next_is(input, TOK_GREAT | TOK_DGREAT))
		redirection.file_descriptor = STDOUT_FILENO;
	else if (lexer_next_is(input, TOK_LESS | TOK_DLESS))
		redirection.file_descriptor = STDIN_FILENO;
	else if (lexer_next_is(input, TOK_IO_DIGIT))
	{
		redirection.file_descriptor = (int)(*input->token.begin - '0');
		lexer_parse_token(input);
	}
	else
		return (unexpect(&input->token));

	if (lexer_next_is(input, TOK_GREAT))
		redirection.operation = REDIR_OUT_TRUNC;
	else if (lexer_next_is(input, TOK_DGREAT))
		redirection.operation = REDIR_OUT_APPEND;
	else if (lexer_next_is(input, TOK_LESS))
		redirection.operation = REDIR_IN_FILE;
	else if (lexer_next_is(input, TOK_DLESS))
		redirection.operation = REDIR_IN_HEREDOC;
	else
		return (unexpect(&input->token));

	lexer_parse_token(input);

	if (!lexer_next_is(input, TOK_WORD))
		return (unexpect(&input->token));
	redirection.argument = token_to_str(&input->token);

	if (!buf_pushback(redir_out, &redirection, 1))
		return (MS_FAIL);
	return (MS_SUCCESS);
}

e_err parse_parameters(t_lexer *input, t_buf *argv_out, t_buf *redir_out)
{
	e_err			status;
	const e_token_type	redir_token =
		TOK_DLESS | TOK_LESS | TOK_DGREAT | TOK_GREAT | TOK_IO_DIGIT;

	if (!lexer_next_is(input, redir_token | TOK_WORD))
	{
		return (unexpect(&input->token));
	}
	status = MS_SUCCESS;
	while (status == MS_SUCCESS)
	{
		if (lexer_next_is(input, TOK_WORD))
			status = parse_argument(input, argv_out);
		else if (lexer_next_is(input, redir_token))
			status = parse_redirection(input, redir_out);
		else
			return (MS_SUCCESS);
		lexer_parse_token(input);
	}
	return (MS_FAIL);
}

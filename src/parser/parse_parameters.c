/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:00:33 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/04 19:32:54 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static e_err	parse_argument(t_token **iterator, t_buf *argv_out)
{
	const char	*argument;

	argument = token_to_str(*iterator);
	*iterator += 1;
	if (!buf_pushback(argv_out, &argument, 1))
		return (MS_FAIL);
	return (MS_SUCCESS);
}

static e_err	parse_redirection(t_token **iterator, t_buf *redir_out)
{
	t_redir	redirection;

	if (token_is(*iterator, TOK_GREAT | TOK_DGREAT))
		redirection.file_descriptor = STDOUT_FILENO;
	else if (token_is(*iterator, TOK_LESS | TOK_DLESS))
		redirection.file_descriptor = STDIN_FILENO;
	else if (token_is(*iterator, TOK_IO_DIGIT))
	{
		redirection.file_descriptor = (int)(*(*iterator)->begin - '0');
		*iterator += 1;
	}
	else
		return (unexpect(*iterator));

	if (token_is(*iterator, TOK_GREAT))
		redirection.operation = REDIR_OUT_TRUNC;
	else if (token_is(*iterator, TOK_DGREAT))
		redirection.operation = REDIR_OUT_APPEND;
	else if (token_is(*iterator, TOK_LESS))
		redirection.operation = REDIR_IN_FILE;
	else if (token_is(*iterator, TOK_DLESS))
		redirection.operation = REDIR_IN_HEREDOC;
	else
		return (unexpect(*iterator));

	*iterator += 1;

	if (!token_is(*iterator, TOK_WORD))
		return (unexpect(*iterator));
	redirection.argument = token_to_str(*iterator);

	if (!buf_pushback(redir_out, &redirection, 1))
		return (MS_FAIL);
	return (MS_SUCCESS);
}

e_err parse_parameters(t_token **iterator, t_buf *argv_out, t_buf *redir_out)
{
	const e_token_type	redir_token =
		TOK_DLESS | TOK_LESS | TOK_DGREAT | TOK_GREAT | TOK_IO_DIGIT;

	if (!token_is(*iterator, redir_token | TOK_WORD))
	{
		return (unexpect(*iterator));
	}
	while (1)
	{
		if (token_is(*iterator, TOK_WORD))
		{
			if (parse_argument(iterator, argv_out) == MS_FAIL)
				break ;
		}
		else if (token_is(*iterator, redir_token))
		{
			if (parse_redirection(iterator, redir_out) == MS_FAIL)
				break ;
		}
		else
		{
			return (MS_SUCCESS);
		}
	}
	return (MS_FAIL);
}

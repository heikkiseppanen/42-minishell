/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:00:33 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/11 15:26:17 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"


static e_err	parse_redir_target(t_token **iterator, int *out)
{
	if (token_is(*iterator, TOK_GREAT | TOK_DGREAT))
	{
		*out = STDOUT_FILENO;
	}
	else if (token_is(*iterator, TOK_LESS | TOK_DLESS))
	{
		*out = STDIN_FILENO;
	}
	else if (token_is(*iterator, TOK_IO_DIGIT))
	{
		*out = (int)(*(*iterator)->begin - '0');
		*iterator += 1;
	}
	else
	{
		return (unexpect(*iterator));
	}
	return (MS_SUCCESS);
}

static e_err	parse_redir_op(t_token **iterator, e_redir_op *out)
{
	if (token_is(*iterator, TOK_GREAT))
	{
		*out = REDIR_OUT_TRUNC;
	}
	else if (token_is(*iterator, TOK_DGREAT))
	{
		*out = REDIR_OUT_APPEND;
	}
	else if (token_is(*iterator, TOK_LESS))
	{
		*out = REDIR_IN_FILE;
	}
	else if (token_is(*iterator, TOK_DLESS))
	{
		*out = REDIR_IN_HEREDOC;
	}
	else
	{
		return (unexpect(*iterator));
	}
	*iterator += 1;
	return (MS_SUCCESS);
}

static e_err	parse_redir_arg(t_token **iterator, const char **out)
{
	if (!token_is(*iterator, TOK_WORD))
	{
		return (unexpect(*iterator));
	}
	*out = token_to_str(*iterator);
	if (!*out)
	{
		return (MS_FAIL);
	}
	return (MS_SUCCESS);
}

static e_err	parse_redirection(t_token **iterator, t_buf *redir_out)
{
	t_redir	redirection;

	if (parse_redir_target(iterator, &redirection.file_descriptor) == MS_FAIL
		|| parse_redir_op(iterator, &redirection.operation) == MS_FAIL
		|| parse_redir_arg(iterator, &redirection.argument) == MS_FAIL
		|| !buf_pushback(redir_out, &redirection, 1))
	{
		return (MS_FAIL);
	}
	return (MS_SUCCESS);
}

static e_err	parse_argument(t_token **iterator, t_buf *argv_out)
{
	const char	*argument;

	argument = token_to_str(*iterator);
	*iterator += 1;
	if (!buf_pushback(argv_out, &argument, 1))
	{
		return (MS_FAIL);
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:12:17 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/29 14:45:35 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "sig.h"


static const char	*parse_redirection_argument(t_token **iterator)
{
	const char	*argument;

	if (!token_is(*iterator, TOK_WORD))
	{
		unexpect(*iterator);
		return (NULL);
	}
	argument = token_to_str(*iterator);
	*iterator += 1;
	return (argument);
}

static t_redir_op	parse_redirection_operation(t_token **iterator)
{
	t_redir_op	operation;

	operation = 0;
	if (token_is(*iterator, TOK_GREAT))
	{
		operation = REDIR_OUT_TRUNC;
	}
	else if (token_is(*iterator, TOK_DGREAT))
	{
		operation = REDIR_OUT_APPEND;
	}
	else if (token_is(*iterator, TOK_LESS))
	{
		operation = REDIR_IN_FILE;
	}
	else if (token_is(*iterator, TOK_DLESS))
	{
		operation = REDIR_IN_HEREDOC;
	}
	else
	{
		unexpect(*iterator);
	}
	*iterator += 1;
	return (operation);
}

static int	parse_redirection_target(t_token **iterator)
{
	if (token_is(*iterator, TOK_GREAT | TOK_DGREAT))
	{
		return (STDOUT_FILENO);
	}
	else if (token_is(*iterator, TOK_LESS | TOK_DLESS))
	{
		return (STDIN_FILENO);
	}
	else if (token_is(*iterator, TOK_IO_DIGIT))
	{
		*iterator += 1;
		return ((int)(*(*iterator - 1)->begin - '0'));
	}
	unexpect(*iterator);
	return (-1);
}

t_err	parse_redirection(t_token **iterator, t_buf *redir_out)
{
	t_redir	rd;

	rd.file_descriptor = parse_redirection_target(iterator);
	rd.operation = parse_redirection_operation(iterator);
	if (!rd.operation || rd.file_descriptor < 0)
	{
		return (MS_FAIL);
	}
	if (rd.operation == REDIR_IN_HEREDOC)
	{
		rd.argument = read_heredoc((*iterator)->begin, (*iterator)->size);
		*iterator += 1;
	}
	else
	{
		rd.argument = parse_redirection_argument(iterator);
	}
	if (!rd.argument || !buf_pushback(redir_out, &rd, 1))
	{
		return (MS_FAIL);
	}
	return (MS_SUCCESS);
}

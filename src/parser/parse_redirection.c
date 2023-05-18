/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 09:12:17 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/18 21:42:25 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include "sig.h"
#include <termios.h>

extern t_shell_state g_state;

static char	*read_here_doc(const char *eof, size_t size)
{
	t_buf	here_doc;
	char	*line;
	struct termios  term;

	tcgetattr(STDIN_FILENO, &term);
	doc_handler();
	if (!buf_init(&here_doc, 16, sizeof(*line)))
		return (NULL);
	while (1)
	{
		term.c_lflag &= ~ECHOCTL;
        tcsetattr(0, TCSANOW, &term);
		line = readline("> ");
		if (!line || ft_memcmp(line, eof, size) == 0 || g_state.heredoc_done)
		{
			if (line)
				free(line);
			if (!buf_pushback(&here_doc, "\0", 1) || g_state.heredoc_done)
			{
				g_state.heredoc_done = 0;
				break ;
			}
			term.c_lflag |= ECHOCTL;
			tcsetattr(0, TCSANOW, &term);
			return (here_doc.data);
		}
		if (!buf_pushback(&here_doc, line, ft_strlen(line))
			|| !buf_pushback(&here_doc, "\n", 1))
			break ;
		free(line);
	}
	buf_del(&here_doc);
	return (NULL);
}

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

static e_redir_op	parse_redirection_operation(t_token **iterator)
{
	e_redir_op	operation;

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

e_err	parse_redirection(t_token **iterator, t_buf *redir_out)
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
		rd.argument = read_here_doc((*iterator)->begin, (*iterator)->size);
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

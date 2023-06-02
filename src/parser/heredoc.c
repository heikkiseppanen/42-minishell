/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:12:55 by hseppane          #+#    #+#             */
/*   Updated: 2023/06/02 10:17:28 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "sig.h"

#include <stdio.h>
#include <readline/readline.h>
#include <termios.h>

static char	*heredoc_readline(const char *prompt)
{
	struct termios	term;
	char			*line;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	line = readline(prompt);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (line);
}

static t_err	read_heredoc_to_buf(const char *eof, size_t size, t_buf *out)
{
	extern t_shell_state	g_state;
	char					*line;

	while (1)
	{
		line = heredoc_readline("heredoc> ");
		if (line && ft_memcmp(line, eof, size) != 0 && !g_state.heredoc_done)
		{
			if (!buf_pushback(out, line, ft_strlen(line))
				|| !buf_pushback(out, "\n", 1))
				break ;
			free(line);
			continue ;
		}
		if (!buf_pushback(out, "\0", 1))
			break ;
		if (line)
			free(line);
		return (MS_SUCCESS);
	}
	if (line)
		free(line);
	return (MS_FAIL);
}

char	*read_heredoc(const char *eof, size_t size)
{
	extern t_shell_state	g_state;
	t_buf					heredoc;

	if (!buf_init(&heredoc, 16, 1))
	{
		return (NULL);
	}
	register_handler(HANDLER_DOC);
	if (read_heredoc_to_buf(eof, size, &heredoc) == MS_FAIL)
	{
		g_state.pipeline_err = 1;
		g_state.heredoc_done = 0;
		buf_del(&heredoc);
		return (NULL);
	}
	g_state.heredoc_done = 0;
	return (heredoc.data);
}

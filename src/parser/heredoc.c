/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 10:12:55 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/29 09:56:22 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "minishell.h"
#include "sig.h"

#include <stdio.h>
#include <readline/readline.h>
#include <termios.h>

char	*read_here_doc(const char *eof, size_t size)
{
	extern t_shell_state g_state;
	t_buf	here_doc;
	char	*line;
	struct termios  term;

	tcgetattr(STDIN_FILENO, &term);
	register_handler(HANDLER_DOC);
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
				g_state.pipeline_err = 1;
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

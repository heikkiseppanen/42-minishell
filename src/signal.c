/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:29:23 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/23 19:42:37 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "minishell.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/ioctl.h>

extern t_shell_state g_state;

void	return_prompt(int signum)
{
	(void)signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	g_state.pipeline_err = 1;
}

void	set_doc(int signum)
{
	(void)signum;
	g_state.heredoc_done = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	register_handler(unsigned char regtype)
{
	if (regtype == HANDLER_SH)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, return_prompt);
	}
	if (regtype == HANDLER_DFL)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
	if (regtype == HANDLER_DOC)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, set_doc);
	}
	if (regtype == HANDLER_IGN)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
}

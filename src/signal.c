/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:29:23 by lsileoni          #+#    #+#             */
/*   Updated: 2023/04/05 17:26:29 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

static void	delete_esc_char(void)
{
	write(1, "\033[1C\033[K\n", 9);
}

static void	clear_line(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		delete_esc_char();
		clear_line();
	}
}

void	init_sighandler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
}

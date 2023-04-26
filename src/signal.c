/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:29:23 by lsileoni          #+#    #+#             */
/*   Updated: 2023/04/03 15:02:22 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>

void	return_prompt(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	clear_line(void)
{
	rl_replace_line("", 1);
	rl_redisplay();
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		return_prompt();
}

void	init_sighandler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
}

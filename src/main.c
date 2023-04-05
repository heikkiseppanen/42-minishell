/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:38:53 by hseppane          #+#    #+#             */
/*   Updated: 2023/04/05 18:30:41 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	struct termios t;
	char	*input;

	tcgetattr(0, &t);
	rl_bind_key('\t', rl_complete);
	using_history();
	init_sighandler();
	while (1)
	{
		t.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &t);
		input = readline("> ");
		t.c_lflag |= ECHOCTL;
		tcsetattr(0, TCSANOW, &t);
		if (!input)
			break ;
		add_history(input);
		free(input);
	}
	return (0);
}

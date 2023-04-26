/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:38:53 by hseppane          #+#    #+#             */
/*   Updated: 2023/03/20 09:35:19 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(void)
{
	char	*input;

	rl_bind_key('\t', rl_complete);
	using_history();
	init_sighandler();
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		add_history(input);
		free(input);
	}
	return (0);
}

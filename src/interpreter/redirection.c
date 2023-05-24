/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:54:05 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/24 10:43:49 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "redir.h"
#include "expand.h"

#include <stdio.h>

void	redir_arg_expand(t_redir *redir)
{
	const char			*old = redir->argument;

	redir->argument = arg_expand(redir->argument);
	free((void *)old);
}

e_err	perform_redirections(t_ast_node *redirections)
{
	const t_redir	*it = redirections->data.redir.array;
	const t_redir	*end = it + redirections->data.redir.size;
	e_err			status;

	if (redirections->type != AST_REDIR)
	{
		return (MS_FAIL);
	}
	status = MS_SUCCESS;
	while (it != end && status == MS_SUCCESS)
	{
		redir_arg_expand((t_redir *)it);
		if (!it->argument)
		{
			return (MS_FAIL);
		}
		status = redir_execute(it);
		++it;
	}
	return (status);
}

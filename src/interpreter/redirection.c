/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:54:05 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/16 21:16:37 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "redir.h"
#include "expand.h"

#include <stdio.h>

e_err	perform_redirections(t_ast_node *redirections)
{
	const t_redir 	*it = redirections->data.redir.array;
	const t_redir 	*end = it + redirections->data.redir.size;
	t_redir 		*tmp;
	e_err			status;

	if (redirections->type != AST_REDIR)
	{
		return (MS_FAIL);
	}
	status = MS_SUCCESS;
	while (it != end && status == MS_SUCCESS)
	{
		tmp = (t_redir *)it;
		tmp->argument = arg_expand(tmp->argument);
		if (!tmp->argument)
		{
			return (MS_FAIL);
		}
		status = redir_execute(tmp);
		++it;
	}
	return (status);
}

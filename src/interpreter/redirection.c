/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 09:54:05 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/10 18:01:27 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "redir.h"

#include <stdio.h>

e_err	perform_redirections(t_ast_node *redirections)
{
	const t_redir 	*it = redirections->data.redir.array;
	const t_redir 	*end = it + redirections->data.redir.size;
	e_err			status;

	if (redirections->type != AST_REDIR)
	{
		return (MS_FAIL);
	}
	status = MS_SUCCESS;
	while (it != end && status == MS_SUCCESS)
	{
		status = redir_execute(it);
		++it;
	}
	return (status);
}

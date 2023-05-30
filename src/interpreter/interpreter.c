/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:58:38 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/29 11:25:53 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "minishell.h"
#include "typedef.h"

t_err	interpret_ast(t_ast_node *node)
{
	extern t_shell_state	g_state;

	if (node->type == AST_PIPE)
	{
		g_state.pipeline_err = execute_pipeline(node);
	}
	if (node->type == AST_COMMAND)
	{
		g_state.pipeline_err = execute_command(node);
	}
	return (MS_FAIL);
}

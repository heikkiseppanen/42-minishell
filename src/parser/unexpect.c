/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 09:54:20 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/04 19:20:24 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

e_err	unexpect(const t_token *token)
{
	ft_fprintf(STDERR_FILENO, "minishell: syntax error near unexpected token ");
	ft_putchar_fd('`', STDERR_FILENO);
	if (token->type == TOK_NULL)
	{
		ft_putstr_fd("newline", STDERR_FILENO);
	}
	else
	{
		write(STDERR_FILENO, token->begin, token->size);
	}
	ft_putstr_fd("\'\n", STDERR_FILENO);
	return (MS_FAIL);
}

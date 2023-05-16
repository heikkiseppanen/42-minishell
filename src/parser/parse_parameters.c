/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:00:33 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/12 13:55:05 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

e_err	parse_parameters(t_token **iterator, t_buf *argv_out, t_buf *redir_out)
{
	e_token_type	redir_token;

	redir_token = TOK_DLESS | TOK_LESS | TOK_DGREAT | TOK_GREAT | TOK_IO_DIGIT;
	if (!token_is(*iterator, redir_token | TOK_WORD))
	{
		return (unexpect(*iterator));
	}
	while (1)
	{
		if (token_is(*iterator, TOK_WORD))
		{
			if (parse_argument(iterator, argv_out) == MS_FAIL)
				break ;
		}
		else if (token_is(*iterator, redir_token))
		{
			if (parse_redirection(iterator, redir_out) == MS_FAIL)
				break ;
		}
		else
		{
			return (MS_SUCCESS);
		}
	}
	return (MS_FAIL);
}

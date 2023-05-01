/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 08:31:36 by hseppane          #+#    #+#             */
/*   Updated: 2023/04/18 14:58:57 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include <libft.h>
#include <stdio.h>

t_token	token_new(e_token_type type, const char *begin, size_t size)
{
	return ((t_token){type, begin, size});
}

void	token_print(const t_token *token)
{
	const char *token_string[] = {
		"EMPTY",
		"WORD",
		"PIPE",
		"IO_NUMBER",
		"REDIR_LESS",
		"REDIR_DLESS",
		"REDIR_GREAT",
		"REDIR_DGREAT"
	};

	printf("Type: %s\n"
			"Expr: \"%.*s\"\n"
			"Size: %lu\n",
			token_string[token->type],
			(int)token->size,
			token->begin,
			token->size);
}

char	*token_to_str(t_token *token)
{
	return (ft_strndup(token->begin, token->size));
}

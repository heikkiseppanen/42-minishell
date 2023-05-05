/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 08:31:36 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/04 15:44:17 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

#include <libft.h>
#include <stdio.h>

t_token	token_new(e_token_type type, const char *begin, size_t size)
{
	return ((t_token){type, begin, size});
}

int	token_is(const t_token *token, e_token_type type_mask)
{
	return (token->type & type_mask);
}

int		token_print(const t_token *token)
{
	int bit;
	const char *type_str[] = {
		"UNKNOWN",
		"NULL",
		"WORD", 
		"PIPE",
		"IO_DIGIT",
		"LESS",
		"DLESS",
		"GREAT",
		"DGREAT", 
	};

	bit = 0;
	if (token->type == TOK_UNKNOWN)
	{
		return (printf("%s\n", type_str[0]));
	}
	while ((e_token_type)(1 << bit) != token->type)
		++bit;
	return (printf("%s, %.*s\n",
			type_str[bit + 1], (int)token->size, token->begin));
}

int	put_token_fd(const t_token *token, int fd)
{
	return (write(fd, token->begin, token->size));
}

char	*token_to_str(t_token *token)
{
	return (ft_strndup(token->begin, token->size));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 08:31:36 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/29 10:00:40 by hseppane         ###   ########.fr       */
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

char	*token_to_str(t_token *token)
{
	return (ft_strndup(token->begin, token->size));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 08:31:36 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/02 07:30:27 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include <libft.h>
#include <stdio.h>

t_token	token_new(e_token_type type, const char *begin, size_t size)
{
	return ((t_token){type, begin, size});
}

int	put_token_fd(const t_token *token, int fd)
{
	return (write(fd, token->begin, token->size));
}

char	*token_to_str(t_token *token)
{
	return (ft_strndup(token->begin, token->size));
}

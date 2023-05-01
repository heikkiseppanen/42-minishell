/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:11:24 by hseppane          #+#    #+#             */
/*   Updated: 2023/04/22 17:29:57 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include <stdio.h>
#include <libft.h>

static char	*str_skip_while(const char *restrict begin, e_bool (while_is)(char))
{
	while (*begin && while_is(*begin) == MS_TRUE)
	{
		++begin;
	}
	return ((char *)begin);
}

static char	*str_skip_until(const char *restrict begin, e_bool (until_is)(char))
{
	while (*begin && until_is(*begin) == MS_FALSE)
	{
		++begin;
	}
	return ((char *)begin);
}

t_lexer	lexer_new(const char *stream_begin)
{
	t_lexer	empty;

	empty.stream = stream_begin;
	lexer_parse_token(&empty);
	return (empty);
}

e_bool	lexer_next_is(t_lexer *lexer, e_token_type type_mask)
{
	return (lexer->token.type & type_mask);
}

void	lexer_parse_token(t_lexer *lexer)
{
	const char	*it = str_skip_while(lexer->stream, char_is_whitespace);
	const char	*begin = it;

	if (!*it)
	{
		lexer->token = token_new(TOK_EOF, begin, 0);
	}
	else if (ft_isdigit(*it))
	{
		++it;
		if (*it == '<' || *it == '>')
		{
			lexer->token = token_new(TOK_IO_NUMBER, begin, it - begin);
		}
		else
		{
			it = str_skip_until(it, char_is_meta);
			lexer->token = token_new(TOK_WORD, begin, it - begin);
		}
	}
	else if (*it == '<')
	{
		if (*(++it) == '<')
			lexer->token = token_new(TOK_DLESS, begin, ++it - begin);
		else
			lexer->token = token_new(TOK_LESS, begin, it - begin);
	}
	else if (*it == '>')
	{
		if (*(++it) == '>')
			lexer->token = token_new(TOK_DGREAT, begin, ++it - begin);
		else
			lexer->token = token_new(TOK_GREAT, begin, it - begin);
	}
	else if (*it == '|')
		lexer->token = token_new(TOK_PIPE, begin, ++it - begin);
	else
	{
		it = str_skip_until(it, char_is_meta);
		lexer->token = token_new(TOK_WORD, begin, it - begin);
	}
	lexer->stream = it;
}

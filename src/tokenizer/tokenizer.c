/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:11:24 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/04 15:11:57 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include <stdio.h>
#include <libft.h>

static const t_token_def	*get_token_lookup_table(void)
{
	static const t_token_def	table[] = {
		{'\0', TOK_NULL},
		{'|', TOK_PIPE},
		{'<', TOK_LESS},
		{'>', TOK_GREAT},
		{-1, TOK_UNKNOWN},
	};
	return (table);
}

static t_token	parse_word_token(const char *begin)
{
	const char *it = begin;

	while (!char_is_meta(*it))
	{
		if (*it == '\'' || *it == '\"')
		{
			it = ft_strchr(it + 1, *it);
			if (!it)
			{
				return (token_new(TOK_UNKNOWN, NULL, 0));
			}
		}
		++it;
	}
	return (token_new(TOK_WORD, begin, it - begin));
}

static t_token	parse_token(const char *begin)
{
	const t_token_def	*lookup = get_token_lookup_table();

	if (ft_isdigit(*begin) && (*(begin + 1) == '<' || *(begin + 1) == '>'))
	{
		return (token_new(TOK_IO_DIGIT, begin, 1));
	}
	while (lookup->type != TOK_UNKNOWN)
	{
		if (lookup->character == *begin)
		{
			if (lookup->type & (TOK_GREAT | TOK_LESS) && *begin == *(begin + 1))
			{
				return (token_new(lookup->type << 1, begin, 2));
			}
			return (token_new(lookup->type, begin, 1));
		}
		++lookup;
	}
	return (parse_word_token(begin));
}

t_token	*tokenize_string(const char *string)
{
	t_buf	token_buffer;
	t_token	token;

	if (!buf_init(&token_buffer, 1, sizeof(token)))
		return (NULL);
	while (1)
	{
		string = str_skip_while(string, ft_isspace);
		token = parse_token(string);
		if (token.type == TOK_UNKNOWN
			|| !buf_pushback(&token_buffer, &token, 1))
			break ;
		if (token.type == TOK_NULL)
		{
			if (!buf_resize(&token_buffer, token_buffer.size))
				break ;
			return (token_buffer.data);
		}
		string += token.size;
	}
	buf_del(&token_buffer);
	return (NULL);
}

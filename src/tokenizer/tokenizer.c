/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:11:24 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/07 14:34:30 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

#include <stdio.h>
#include <libft.h>

static const t_token_def	*get_token_lookup_table(void)
{
	static const t_token_def	table[] = {
		{'\0', TOK_NULL},
		{'\n', TOK_NULL},
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
	const char *pair;

	while (!char_is_meta(*it))
	{
		if (*it == '\'' || *it == '\"')
		{
			pair = ft_strchr(it + 1, *it);
			if (!pair)
			{
				ft_fprintf(STDERR_FILENO,
					"syntax error, '%c' missing a pair\n", *it);
				return (token_new(TOK_UNKNOWN, NULL, 0));
			}
			it = pair;
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
	t_buf	tokens;
	t_token	current;

	string = str_skip_while(string, ft_isspace);
	if (!*string || !buf_init(&tokens, 1, sizeof(current)))
	{
		return (NULL);
	}
	while (1)
	{
		current = parse_token(string);
		if (current.type == TOK_UNKNOWN || !buf_pushback(&tokens, &current, 1))
		{
			break ;
		}
		if (current.type == TOK_NULL)
		{
			return (tokens.data);
		}
		string += current.size;
		string = str_skip_while(string, ft_isspace);
	}
	buf_del(&tokens);
	return (NULL);
}

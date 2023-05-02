/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 08:26:08 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/02 07:13:19 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  TOKENIZER_H
# define  TOKENIZER_H

# include "typedef.h"

# include <stdlib.h>

typedef enum e_token_type
{
	TOK_UNKNOWN = 0,
	TOK_EOF = 1,
	TOK_WORD = 1 << 1,
	TOK_PIPE = 1 << 2,
	TOK_IO_DIGIT = 1 << 3,
	TOK_LESS = 1 << 4,
	TOK_DLESS = 1 << 5,
	TOK_GREAT = 1 << 6,
	TOK_DGREAT = 1 << 7,
}	e_token_type;

typedef struct s_token
{
	e_token_type	type;
	const char		*begin;
	size_t			size;
}	t_token;

typedef struct s_lexer
{
	const char	*stream;
	t_token		token;
}	t_lexer;

t_lexer	lexer_new(const char *stream_begin);
void	lexer_parse_token(t_lexer *lexer);
e_bool	lexer_next_is(t_lexer *lexer, e_token_type type_mask);

t_token	token_new(enum e_token_type type, const char *begin, size_t size);
void	token_print(const t_token *token);
char	*token_to_str(t_token *token);

e_bool	char_is_meta(char c);
e_bool	char_is_whitespace(char c);
e_bool	char_is_digit(char c);

#endif

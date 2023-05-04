/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 08:26:08 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/04 14:21:42 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  TOKENIZER_H
# define  TOKENIZER_H

# include "typedef.h"

# include <stdlib.h>

typedef enum e_token_type
{
	TOK_UNKNOWN = 0,
	TOK_NULL = 1,
	TOK_WORD = 1 << 1,
	TOK_PIPE = 1 << 2,
	TOK_IO_DIGIT = 1 << 3,
	TOK_LESS = 1 << 4,
	TOK_DLESS = 1 << 5,
	TOK_GREAT = 1 << 6,
	TOK_DGREAT = 1 << 7,
}	e_token_type;

typedef struct s_token_def
{
	char			character;
	e_token_type	type;
}	t_token_def;

typedef struct s_token
{
	e_token_type	type;
	const char		*begin;
	size_t			size;
}	t_token;

t_token	*tokenize_string(const char *string);

t_token	token_new(e_token_type type, const char *begin, size_t size);
int		token_is(const t_token *token, e_token_type type_mask);
int		token_print(const t_token *token);
int		put_token_fd(const t_token *token, int fd);

char	*str_skip_while(const char *restrict begin, int (while_is)(int));
char	*str_skip_until(const char *restrict begin, int (until_is)(int));

int		char_is_meta(int c);

#endif

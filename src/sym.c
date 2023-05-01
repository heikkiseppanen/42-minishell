/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sym.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:37:39 by hseppane          #+#    #+#             */
/*   Updated: 2023/04/18 14:58:15 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#include <libft.h>

e_bool	char_is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

e_bool	char_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

e_bool	char_is_meta(char c)
{
	return (char_is_whitespace(c) 
			|| c == '|' || c == '<' || c == '>');
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 11:48:21 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/12 11:48:34 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

e_err	parse_argument(t_token **iterator, t_buf *argv_out)
{
	const char	*argument;

	argument = token_to_str(*iterator);
	*iterator += 1;
	if (!buf_pushback(argv_out, &argument, 1))
	{
		return (MS_FAIL);
	}
	return (MS_SUCCESS);
}

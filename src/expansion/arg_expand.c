/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:45:25 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/09 11:38:59 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/ft/buf.h"
#include "minishell.h"
#include "expand.h"

static void	open_quote(t_sym_state *s_s, const char *string)
{
	s_s->openchar = '"';
	if (string[s_s->i] == '\'')
		s_s->openchar = '\'';
	s_s->open = 1;
}

static void	close_quote(t_sym_state *s_s)
{
	s_s->openchar = 0;
	s_s->open = -1;
}

static int	process_tokenstream(t_sym_state *s_s, const char *string)
{
	int	exp_ret;

	while (string[s_s->i])
	{
		if ((string[s_s->i] == '"' || string[s_s->i] == '\'') && s_s->open < 0)
			open_quote(s_s, string);
		else if ((string[s_s->i] == s_s->openchar) && s_s->open > 0)
			close_quote(s_s);
		else if ((string[s_s->i] == '$')
			&& (s_s->openchar == '"' || s_s->open < 0))
		{
			exp_ret = handle_exp(s_s, string);
			if (!exp_ret)
				return (0);
			if (exp_ret == 1)
				continue ;
			break ;
		}
		else if (!buf_pushback(s_s->buf, (void *)(&string[s_s->i]), 1))
			return (0);
		s_s->i++;
	}
	return (1);
}

char	*arg_expand(const char *string)
{
	t_sym_state	s;
	t_buf		buf;
	char		*expanded;

	s.i = 0;
	s.open = -1;
	s.openchar = 0;
	s.buf = &buf;
	if (!(buf_init(s.buf, 1024, 1)) || !process_tokenstream(&s, string)
		|| !buf_pushback(s.buf, "", 1))
	{
		if (s.buf)
			buf_del(s.buf);
		perror("minishell");
		return (NULL);
	}
	expanded = ft_strdup((char *)s.buf->data);
	if (!expanded)
		perror("minishell");
	buf_del(s.buf);
	return (expanded);
}

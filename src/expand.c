/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:45:25 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/12 18:09:31 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../third-party/libft/libft.h"
#include "include/ft/buf.h"
#include "minishell.h"

extern t_shell_state g_state;

typedef struct s_exp_state
{
	char	openchar;
	t_buf	*buf;
	int		open;
	int		i;
}	t_exp_state;

int	handle_exp(t_exp_state *s, const char *string)
{
	char	*env;
	char	*envres;
	int		i;

	i = s->i;
	while (string[i] && ft_isalnum(string[i]))
		i++;
	env = malloc((i - s->i) + 2);
	if (!env)
	{
		buf_del(s->buf);
		return (0);
	}
	i = 0;
	if (string[s->i] == '?')
	{
		envres = ft_itoa(g_state.pipeline_err);
		if (!envres)
		{
			buf_del(s->buf);
			free(env);
			return (0);
		}
		if (!buf_pushback(s->buf, envres, ft_strlen(envres)))
		{
			buf_del(s->buf);
			free(env);
			free(envres);
			return (0);
		}
		free(envres);
		s->i++;
		return (1);
	}
	else if (string[s->i] == '_')
	{
		env[i] = '_';
		i++;
		s->i++;
	}
	else
	{
		if (!string[s->i])
		{
			if (!buf_pushback(s->buf, "$", 1))
			{
				buf_del(s->buf);
				free(env);
				return (0);
			}
			return (1);
		}
		if (!ft_isalpha(string[s->i]))
		{
			if (!buf_pushback(s->buf, (void *)((&string[s->i])-1), 2))
			{
				buf_del(s->buf);
				free(env);
				return (0);
			}
			s->i++;
			return (1);
		}
	}
	i = 0;
	while (string[s->i] && ft_isalnum(string[s->i]))
	{
		env[i] = string[s->i];
		s->i++;
		i++;
	}
	env[i] = '\0';
	envres = ft_htable_get(g_state.envp, env);
	free(env);
	if (!envres)
		return (1);
	if (!buf_pushback(s->buf, envres, ft_strlen(envres)))
	{
		buf_del(s->buf);
		return (0);
	}
	if (!string[s->i])
		return (2);
	return (1);
}

char	*str_expand(const char *string)
{
	t_exp_state	s;
	int			rval;
	char		*expanded;

	s.i = 0;
	s.open = -1;
	s.openchar = 0;
	s.buf = malloc(sizeof(t_buf));
	if (!s.buf || !(buf_init(s.buf, 1024, 1)))
		return (NULL);
	while(string[s.i])
	{
		if ((string[s.i] == '"' || string[s.i] == '\'') && s.open < 0)
		{
			s.openchar = '"';
			if (string[s.i] == '\'')
				s.openchar = '\'';
			s.open = 1;
		}
		else if ((string[s.i] == s.openchar) && s.open > 0)
		{
			s.openchar = 0;
			s.open = -1;
		}
		else if ((string[s.i] == '$') && (s.openchar == '"' || s.open < 0))
		{
			s.i++;
			rval = handle_exp(&s, string);
			if (!rval)
				return (NULL);
			if (rval == 1)
				continue ;
			break ;
		}
		else
		{
			if (!buf_pushback(s.buf, (void *)(&string[s.i]), 1))
				return (NULL);
		}
		s.i++;
	}
	if (!buf_pushback(s.buf, "", 1))
		return (NULL);
	expanded = ft_strdup((char *)s.buf->data);
	buf_del(s.buf);
	return (expanded);
}

char	**expand_arglist(char **argv)
{
	char	**expanded;
	size_t	i;

	if (!argv)
		return (NULL);
	i = 0;
	expanded = NULL;
	while (argv[i])
		i++;
	expanded = malloc(sizeof(char *) * (i + 1));
	if (!expanded)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		expanded[i] = str_expand(argv[i]);
		i++;
	}
	expanded[i] = NULL;
	return (expanded);
}

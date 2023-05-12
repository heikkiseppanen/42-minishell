/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:45:25 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/12 20:17:35 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../third-party/libft/libft.h"
#include "include/ft/buf.h"
#include "minishell.h"

extern t_shell_state g_state;

typedef struct s_sym_state
{
	t_buf	*buf;
	int		open;
	int		i;
	char	openchar;
}	t_sym_state;

typedef struct s_exp_state
{
	char	*env;
	char	*envres;
	int		i;
}	t_exp_state;

void	check_underscore(t_sym_state *s_s, t_exp_state *e_s, const char *string)
{
	if (string[s_s->i] == '_')
	{
		e_s->env[e_s->i] = '_';
		e_s->i++;
		s_s->i++;
	}
}

int	check_questionmark(t_sym_state *s, char *envres, char *env)
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

static char	*alloc_env(t_sym_state *s, const char *string)
{
	char	*res;
	int		i;

	i = s->i;
	while (string[i] && ft_isalnum(string[i]))
		i++;
	res = ft_calloc(i + 2, 1);
	if (!res)
	{
		buf_del(s->buf);
		return (NULL);
	}
	return (res);
}

static int	check_null(t_sym_state *s, char *env)
{
	if (!buf_pushback(s->buf, "$", 1))
	{
		buf_del(s->buf);
		free(env);
		return (0);
	}
	return (1);
}

static int	check_other(t_sym_state *s, char *env, const char *string)
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

static int	check_first_tok(t_sym_state *s_s, t_exp_state *e_s, const char *string)
{
	if (string[s_s->i] == '?')
		return (check_questionmark(s_s, e_s->envres, e_s->env));
	else
	{
		if (!string[s_s->i])
			return (check_null(s_s, e_s->env));
		if (!ft_isalpha(string[s_s->i]))
			return (check_other(s_s, e_s->env, string));
	}
	return (0);
}

static void	grab_env_str(t_sym_state *s_s, t_exp_state *e_s, const char *string)
{
	e_s->i = 0;
	while (string[s_s->i] && ft_isalnum(string[s_s->i]))
	{
		e_s->env[e_s->i] = string[s_s->i];
		s_s->i++;
		e_s->i++;
	}
	e_s->env[e_s->i] = '\0';
}

int	handle_exp(t_sym_state *s_s, const char *string)
{
	t_exp_state e_s;

	e_s.env = alloc_env(s_s, string);
	if (!e_s.env)
		return (0);
	if (string[s_s->i] == '?' || !string[s_s->i] || !ft_isalpha(string[s_s->i]))
		return (check_first_tok(s_s, &e_s, string));
	check_underscore(s_s, &e_s, string);
	grab_env_str(s_s, &e_s, string);
	e_s.envres = ft_htable_get(g_state.envp, e_s.env);
	free(e_s.env);
	if (!e_s.envres)
		return (1);
	if (!buf_pushback(s_s->buf, e_s.envres, ft_strlen(e_s.envres)))
	{
		buf_del(s_s->buf);
		return (0);
	}
	if (!string[s_s->i])
		return (2);
	return (1);
}

char	*str_expand(const char *string)
{
	t_sym_state	s;
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

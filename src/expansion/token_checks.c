/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:39:13 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/13 04:03:26 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"

extern t_shell_state	g_state;

static int	check_questionmark(t_sym_state *s, char *envres, char *env)
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
	if (!buf_pushback(s->buf, (void *)((&string[s->i]) - 1), 2))
	{
		buf_del(s->buf);
		free(env);
		return (0);
	}
	s->i++;
	return (1);
}

void	check_underscore(t_sym_state *s_s, t_exp_state *e_s, const char *string)
{
	if (string[s_s->i] == '_')
	{
		e_s->env[e_s->i] = '_';
		e_s->i++;
		s_s->i++;
	}
}

int	check_first_tok(t_sym_state *s_s, t_exp_state *e_s, const char *string)
{
	if ((string[s_s->i] == '"' || string[s_s->i] == '\'') && (s_s->open > 0))
		return (check_null(s_s, e_s->env));
	if ((string[s_s->i] == '"' || string[s_s->i] == '\'') && (s_s->open < 0))
		return (1);
	if (string[s_s->i] == '?')
		return (check_questionmark(s_s, e_s->envres, e_s->env));
	if (!string[s_s->i])
		return (check_null(s_s, e_s->env));
	if (!ft_isalpha(string[s_s->i]))
		return (check_other(s_s, e_s->env, string));
	return (0);
}

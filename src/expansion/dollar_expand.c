/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 22:35:52 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/22 18:54:49 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"

extern t_shell_state	g_state;

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

int	handle_exp(t_sym_state *s_s, const char *string)
{
	t_exp_state	e_s;

	s_s->i++;
	e_s.env = alloc_env(s_s, string);
	if (!e_s.env)
		return (0);
	if (string[s_s->i] == '?' || !string[s_s->i] || !ft_isalpha(string[s_s->i]))
	{
		free(e_s.env);
		return (check_first_tok(s_s, &e_s, string));
	}
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

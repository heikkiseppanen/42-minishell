/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:45:25 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/11 20:18:11 by lsileoni         ###   ########.fr       */
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
}	t_exp_state;

int	handle_exp(t_exp_state *s, char **string)
{
	char	*env;
	char	*envres;
	int		i;

	i = 0;
	while ((*string)[i] && ft_isalnum((*string)[i]))
		i++;
	env = malloc(i + 1);
	if (!env)
	{
		buf_del(s->buf);
		return (0);
	}
	i = 0;
	if (**string == '?')
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
		(*string)++;
		return (1);
	}
	else if (**string == '_')
	{
		env[i] = '_';
		i++;
		(*string)++;
	}
	else
	{
		if (!ft_isalpha(**string))
		{
			if (!buf_pushback(s->buf, (void *)(string[-1]), 1))
			{
				buf_del(s->buf);
				free(env);
				return (0);
			}
			return (1);
		}
	}
	while (**string && ft_isalnum(**string))
	{
		env[i] = **string;
		(*string)++;
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
	if (!(*string))
		return (2);
	return (1);
}



char	*str_expand(const char *string)
{
	t_exp_state	state;
	int			rval;
	char		*expanded;

	state.open = -1;
	state.openchar = 0;
	state.buf = malloc(sizeof(t_buf));
	if (!state.buf || !(buf_init(state.buf, 1024, 1)))
		return (NULL);
	while(*string)
	{
		if ((*string == '"' || *string == '\'') && state.open < 0)
		{
			state.openchar = '"';
			if (*string == '\'')
				state.openchar = '\'';
			state.open = 1;
		}
		else if ((*string == state.openchar) && state.open > 0)
		{
			state.openchar = 0;
			state.open = -1;
		}
		else if ((*string == '$') && (state.openchar == '"' || state.open < 0))
		{
			string++;
			rval = handle_exp(&state, (char **)&string);
			if (!rval)
				return (NULL);
			if (rval == 1)
				continue ;
			break ;
		}
		else
		{
			if (!buf_pushback(state.buf, (void *)string, 1))
				return (NULL);
		}
		string++;
	}
	expanded = ft_strdup((char *)state.buf->data);
	buf_del(state.buf);
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

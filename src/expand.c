/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:45:25 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/09 10:01:34 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../third-party/libft/libft.h"
#include "minishell.h"

extern t_shell_state g_state;

char	*str_expand(const char *string)
{
	int		i;
	char	openchar;
	char	*env;
	char	*envres;
	t_buf	*buf;
	int		open;

	open = -1;
	openchar = 0;
	buf = malloc(sizeof(t_buf));
	buf_init(buf, 1024, 1);
	while(*string)
	{
		if ((*string == '"' || *string == '\'') && open < 0)
		{
			openchar = '"';
			if (*string == '\'')
				openchar = '\'';
			open = 1;
		}
		else if ((*string == openchar) && open > 0)
		{
			openchar = 0;
			open = -1;
		}
		else if ((*string == '$') && (openchar == '"' || open < 0))
		{
			i = 0;

			while (string[i] && ft_isalnum(string[i]))
				i++;
			env = malloc(i + 1);
			i = 0;
			string++;
			if (*string == '?')
			{
				envres = ft_itoa(g_state.pipeline_err);
				buf_pushback(buf, envres, ft_strlen(envres));
				string++;
				continue ;
			}
			else if (*string == '_')
			{
				env[i] = '_';
				i++;
				string++;
			}
			else if (ft_isalpha(*string))
				printf(" ");
			else
			{
				buf_pushback(buf, (void *)&(string[-1]), 1);
				continue ;
			}
			while (*string && ft_isalnum(*string))
			{
				env[i] = *string;
				string++;
				i++;
			}
			env[i] = '\0';
			envres = ft_htable_get(g_state.envp, env);
			free(env);
			if (!envres)
				continue ;
			buf_pushback(buf, envres, ft_strlen(envres));
			if (!(*string))
				break ;
			continue ;
		}
		else
			buf_pushback(buf, (void *)string, 1);
		string++;
	}
	return ((char *)buf->data);
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

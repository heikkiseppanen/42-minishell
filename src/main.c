/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:38:53 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/08 13:45:55 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sig.h"
#include "tokenizer.h"
#include "ast.h"
#include "libft.h"
#include "sig.h"
#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char 	**environ;
t_shell_state 	g_state;

t_htable	*grab_environment_variables()
{
	t_htable		*envtable;
	unsigned int	i;
	unsigned int	j;
	char			*key;
	char			*value;

	envtable = ft_htable_create(1024);
	while (*environ)
	{
		i = 0;
		while ((*environ)[i] != '=' && (*environ)[i])
			i++;
		key = malloc(i + 1);
		key[i] = '\0';
		ft_memcpy(key, *environ, i);
		j = i + 1;
		i = ft_strlen(&((*environ)[i + 1]));
		value = malloc(i + 1);
		ft_memcpy(value, &((*environ)[j]), i + 1);
		ft_htable_insert(envtable, key, value);
		free(key);
		environ++;
	}
	return (envtable);
}

char	**htable_to_environ(t_htable *envp)
{
	char			**env;
	char			*tmp;
	unsigned int	i;
	unsigned int	j;

	env = malloc(sizeof(char *) * (envp->size + 1));
	if (!env)
		return (NULL);
	i = 0;
	j = 0;
	while (i < envp->cap)
	{
		if (envp->memory[i])
		{
			tmp = ft_strjoin(envp->memory[i]->key, "=");
			env[j] = ft_strjoin(tmp, envp->memory[i]->value);
			free(tmp);
			j++;
		}
		i++;
	}
	env[j] = NULL;
	return (env);
}

e_err	handle_input(const char *input)
{
	t_token	*const	tokenized_input = tokenize_string(input);
	t_token		*token_iterator;
	t_ast_node	*syntax_tree;
	e_err		status;

	if (!tokenized_input)
		return (MS_FAIL);
	token_iterator = tokenized_input;
	syntax_tree = parse_pipeline(&token_iterator);
	free(tokenized_input);
	if (!syntax_tree)
		return (MS_FAIL);
	status = interpret_ast(syntax_tree);
	ast_node_del(syntax_tree);
	return (status);
}

void	print_environ(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int	main(void)
{
	char	*input;

	g_state.envp = grab_environment_variables();
	ft_htable_insert(g_state.envp, "SHLVL", ft_itoa(ft_atoi(ft_htable_get(g_state.envp, "SHLVL")) + 1));
	rl_bind_key('\t', rl_complete);
	using_history();
	init_sighandler();
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		handle_input(input);
		add_history(input);
		free(input);
	}
	return (0);
}

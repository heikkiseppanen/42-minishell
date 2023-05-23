/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 08:38:53 by hseppane          #+#    #+#             */
/*   Updated: 2023/05/22 22:06:34 by lsileoni         ###   ########.fr       */
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
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

extern char 	**environ;
t_shell_state 	g_state;

static int	increment_shlvl()
{
	char			*tmp;
	int				shlvl;

	tmp = ft_htable_get(g_state.envp, "SHLVL");
	if (!tmp)
	{
		ft_htable_insert(g_state.envp, "SHLVL", ft_itoa(1));
		return (1);
	}
	shlvl = ft_atoi(tmp);
	if (ft_htable_remove(g_state.envp, "SHLVL") == -1)
		return (0);
	if (!ft_htable_insert(g_state.envp, "SHLVL", ft_itoa(shlvl + 1)))
		return (0);
	return (1);
}

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

void	shell_repl(struct termios *term)
{
	char			*input;

	tcgetattr(STDIN_FILENO, term);
	while (1)
	{
		init_sighandler();
		term->c_lflag &= ~ECHOCTL;
        tcsetattr(0, TCSANOW, term);
        input = readline("> ");
        term->c_lflag |= ECHOCTL;
        tcsetattr(0, TCSANOW, term);
		if (!input)
			break ;
		handle_input(input);
		if (ft_strncmp("", input, 1))
			add_history(input);
		free(input);
	}
}

int	main(void)
{
	struct termios  term;

	tcgetattr(STDIN_FILENO, &term);
	g_state.envp = grab_environment_variables();
	g_state.heredoc_done = 0;
	if (!increment_shlvl())
	{
		perror("Failed to increment shell level");
		exit (1);
	}
	shell_repl(&term);
	write(1, "exit\n", 5);
	exit (g_state.pipeline_err);
	return (0);
}

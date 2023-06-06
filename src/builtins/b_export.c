/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 04:09:17 by lsileoni          #+#    #+#             */
/*   Updated: 2023/06/06 15:52:06 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"
#include "libft.h"

static int	assign_value(char **var_val, char **value, unsigned char *valid)
{
	size_t	i;

	if (!var_val || !(*valid))
		return (0);
	if (!var_val[0])
	{
		free(var_val);
		return (0);
	}
	if (!var_val[1])
		*value = ft_strdup("");
	else
		*value = var_val[1];
	if (!(*value))
		return (0);
	if (ft_isdigit(var_val[0][0]))
		return (0);
	i = -1;
	while ((*var_val)[++i])
		if (!(ft_isalnum((*var_val)[i]) || (*var_val)[i] == '_'))
			return (0);
	return (1);
}

static const char	**init_key_value(char *arg)
{
	size_t			arg_len;
	const char		**key_value = ft_calloc(sizeof(char **) * 3, 1);

	if (!key_value)
		return (NULL);
	if (!arg)
	{
		free(key_value);
		return (NULL);
	}
	arg_len = ft_strlen(arg) + 1;
	key_value[0] = ft_calloc(arg_len, 1);
	key_value[1] = ft_calloc(arg_len, 1);
	if (!key_value[0] || !key_value[1])
	{
		if (key_value[0])
			free((void *)key_value[0]);
		if (key_value[1])
			free((void *)key_value[1]);
		free(key_value);
		return (NULL);
	}
	return (key_value);
}

static char	**get_empty_key(char **key_value, char *arg)
{
	extern t_shell_state	g_state;
	char					*tmp;

	tmp = ft_htable_get(g_state.envp, arg);
	if (tmp && ft_memcmp(tmp, "", 2))
	{
		destroy_mult_value(key_value, key_value[0], key_value[1], key_value[2]);
		return (NULL);
	}
	free(key_value[0]);
	key_value[0] = NULL;
	key_value[0] = ft_strdup(arg);
	if (!key_value[0])
	{
		free(key_value);
		return (NULL);
	}
	free(key_value[1]);
	key_value[1] = NULL;
	return (key_value);
}

static char	**get_key_value(char *arg, unsigned char *valid)
{
	const char	**key_value = (const char **)init_key_value(arg);
	size_t		i;
	size_t		j;

	if (!key_value)
		return (NULL);
	if ((!ft_isalpha(*arg) && *arg != '_'))
		return ((char **)key_value + (*valid = 0));
	i = 0;
	while (arg[++i] && arg[i] != '=')
	{
		if ((!ft_isalnum(arg[i]) && arg[i] != '='))
			return ((char **)key_value + (*valid = 0));
	}
	if (!arg[i])
		return (get_empty_key((char **)key_value, arg));
	i = -1;
	while (arg[++i] != '=')
		((char **)(key_value))[0][i] = arg[i];
	if (!arg[i + 1])
		return ((char **)key_value);
	j = 0;
	while (arg[++i] && ++j)
		((char **)(key_value))[1][j - 1] = arg[i];
	return ((char **)key_value);
}

int	export_var(char **argv)
{
	extern t_shell_state	g_state;
	char					**var_val;
	char					*value;
	size_t					cur_arg;
	unsigned char			valid;

	cur_arg = 0;
	if (!argv[1])
		return (put_exp());
	while (argv[cur_arg++])
	{
		valid = 1;
		var_val = get_key_value(argv[cur_arg], &valid);
		if (!valid)
		{
			destroy_mult_value(var_val, var_val[0], var_val[1], var_val[2]);
			ft_fprintf(2, "minishell: export: `%s`: not a valid identifier\n",
				argv[cur_arg]);
		}
		if (!assign_value(var_val, &value, &valid))
			continue ;
		ft_htable_insert(g_state.envp, var_val[0], value);
		destroy_mult_value(var_val, var_val[0], NULL, NULL);
	}
	return (0);
}

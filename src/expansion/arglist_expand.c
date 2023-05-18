/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arglist_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsileoni <lsileoni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:55:29 by lsileoni          #+#    #+#             */
/*   Updated: 2023/05/17 06:41:42 by lsileoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expand.h"

int	only_quotes(char *str)
{
	char	qtype;
	int		i;

	i = 0;
	qtype = *str;
	if (!(qtype == '"' || qtype == '\''))
		return (0);
	while (str[i])
	{
		if (str[i] != qtype)
			return (0);
		i++;
	}
	return (1);
}

char	**return_expanded_list(char **argv, size_t count)
{
	char	**complete_list;
	size_t	elem_count;
	size_t	i;
	size_t	j;

	elem_count = 0;
	i = 0;
	while (i < count)
	{
		if (argv[i])
			elem_count++;
		i++;
	}
	if (!elem_count)
		return (NULL);
	complete_list = ft_calloc(elem_count + 1, sizeof(char *));
	j = 0;
	i = 0;
	while (i < count)
	{
		if (argv[i])
		{
			complete_list[j] = argv[i];
			argv[i] = NULL;
			j++;
		}
		i++;
	}
	complete_list[j] = NULL;
	free(argv);
	return (complete_list);
}

char	**expand_arglist(char **argv)
{
	char	**expanded;
	char	*tmp;
	size_t	count;
	size_t	i;

	if (!argv)
		return (NULL);
	count = 0;
	expanded = NULL;
	while (argv[count])
		count++;
	expanded = ft_calloc((sizeof(char *) * (count)), 1);
	if (!expanded)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		tmp = arg_expand(argv[i]);
		if (only_quotes(argv[i]))
			expanded[i] = ft_strdup("");
		else if (tmp && ft_strlen(tmp))
			expanded[i] = arg_expand(argv[i]);
		free(tmp);
		i++;
	}
	return (return_expanded_list(expanded, count));
}

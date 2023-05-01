/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:14:21 by hseppane          #+#    #+#             */
/*   Updated: 2023/03/27 13:14:24 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*str_skip_while(const char *restrict begin, int (while_is)(int))
{
	while (*begin && while_is(*begin))
	{
		++begin;
	}
	return ((char *)begin);
}

char	*str_skip_until(const char *restrict begin, int (until_is)(int))
{
	while (*begin && !until_is(*begin))
	{
		++begin;
	}
	return ((char *)begin);
}

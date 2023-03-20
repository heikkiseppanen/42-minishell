/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:08:26 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/20 11:54:40 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strflds(char const *str, const char delim)
{
	int	fields;

	fields = 0;
	while (*str)
	{
		while (*str == delim)
			str++;
		if (*str)
		{
			fields++;
			while (*str != delim && *str)
				str++;
		}
	}
	return (fields);
}

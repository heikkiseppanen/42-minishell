/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strflds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:25:14 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/20 10:25:40 by hseppane         ###   ########.fr       */
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

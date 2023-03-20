/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 09:01:07 by hseppane          #+#    #+#             */
/*   Updated: 2022/12/09 10:50:49 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdarg.h>

static int	print_arg(va_list *args, char tok)
{
	if (tok == 'c')
		return (ft_write_char((char)va_arg(*args, int)));
	else if (tok == 's')
		return (ft_write_str(va_arg(*args, const char *)));
	else if (tok == 'p')
		return (ft_putptr(va_arg(*args, void *)));
	else if (tok == 'd')
		return (ft_putdec_i64(va_arg(*args, int)));
	else if (tok == 'i')
		return (ft_putdec_i64(va_arg(*args, int)));
	else if (tok == 'u')
		return (ft_putdec_u64(va_arg(*args, unsigned int)));
	else if (tok == 'x')
		return (ft_puthex_lower_u64(va_arg(*args, unsigned int)));
	else if (tok == 'X')
		return (ft_puthex_upper_u64(va_arg(*args, unsigned int)));
	else if (tok == '%')
		return (ft_write_char('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	const char	*it = str;
	va_list		arg_list;
	size_t		toklen;
	int			total_write;

	va_start(arg_list, str);
	total_write = 0;
	while (*it)
	{
		if (*it != '%')
		{
			toklen = ft_toklen(it, '%');
			total_write += write(STDOUT_FD, it, toklen);
			it += toklen;
		}
		else
		{
			total_write += print_arg(&arg_list, *++it);
			it++;
		}
	}
	va_end(arg_list);
	return (total_write);
}

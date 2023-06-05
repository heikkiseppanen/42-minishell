/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hseppane <marvin@42.ft>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 09:01:07 by hseppane          #+#    #+#             */
/*   Updated: 2023/06/05 11:20:39 by hseppane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdarg.h>

static int	fprint_arg(int fd, va_list *args, char tok)
{
	if (tok == 'c')
		return (ft_putchar_fd((char)va_arg(*args, int), fd));
	else if (tok == 's')
		return (ft_putstr_fd(va_arg(*args, const char *), fd));
	else if (tok == 'p')
		return (ft_putptr_fd(va_arg(*args, void *), fd));
	else if (tok == 'd')
		return (ft_putdec_i64_fd(va_arg(*args, int), fd));
	else if (tok == 'i')
		return (ft_putdec_i64_fd(va_arg(*args, int), fd));
	else if (tok == 'u')
		return (ft_putdec_u64_fd(va_arg(*args, unsigned int), fd));
	else if (tok == 'x')
		return (ft_puthex_lower_u64_fd(va_arg(*args, unsigned int), fd));
	else if (tok == 'X')
		return (ft_puthex_upper_u64_fd(va_arg(*args, unsigned int), fd));
	else if (tok == '%')
		return (ft_putchar_fd('%', fd));
	return (0);
}

static int	ft_fprintf_va_list(int fd, const char *format, va_list *args)
{
	int	total_write;
	int	token_length;

	total_write = 0;
	while (*format)
	{
		if (*format != '%')
		{
			token_length = ft_toklen(format, '%');
			total_write += write(fd, format, token_length);
			format += token_length;
		}
		else
		{
			total_write += fprint_arg(fd, args, *(++format));
			++format;
		}
	}
	return (total_write);
}

int	ft_printf(const char *str, ...)
{
	va_list		arg_list;
	int			total_write;

	va_start(arg_list, str);
	total_write = ft_fprintf_va_list(STDOUT_FILENO, str, &arg_list);
	va_end(arg_list);
	return (total_write);
}

int	ft_fprintf(int fd, const char *str, ...)
{
	va_list		arg_list;
	int			total_write;

	va_start(arg_list, str);
	total_write = ft_fprintf_va_list(fd, str, &arg_list);
	va_end(arg_list);
	return (total_write);
}

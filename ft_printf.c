/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maljean <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 23:48:08 by maljean           #+#    #+#             */
/*   Updated: 2018/06/08 16:39:13 by maljean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_ctoa(char c)
{
	char	*s;
	
	s = (char*)malloc(sizeof(char) * 2);
	s[0] = c;
	s[1] = '\0';
	return (s);
}

void	ft_printf2(const char *format, va_list args, int i, int *bytes)
{
	t_ops		ops;

	while (format[++i])
	{
		ft_init_ops(&ops);
		if (format[i] == '%' && format[i + 1] == '%')
		{
			ft_putchar('%', &ops);
			i += 1;
		}
		else if (format[i] == '%')
		{
			if (ft_parse((char*)format, &i, &ops, args))
				ft_handle_it(&ops, args);
			else if (format[i])
				ft_putchar(format[i], &ops);
		}
		else if (i < ft_strlen((char*)format))
			ft_putchar(format[i], &ops);
		*bytes += ops.bytes;
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;
	int			bytes;

	i = -1;
	bytes = 0;
	va_start(args, format);
	ft_printf2(format, args, -1, &bytes);
	va_end(args);
	return (bytes);
}

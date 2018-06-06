/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maljean <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 01:59:53 by maljean           #+#    #+#             */
/*   Updated: 2018/06/06 02:31:27 by maljean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, t_ops *ops)
{
	write(1, &c, 1);
	ops->bytes += 1;
}

void	ft_putstr(char *s, t_ops *ops, int i)
{
	if (!s)
	{
		write(1, "(null)", 6);
		return ;
	}
	while (s[++i])
	{
		write(1, &s[i], 1);
		ops->bytes += 1;
	}
}

char	*ft_strrev(char *str, int i, int length)
{
	char	buff;

	while (str[length])
		length++;
	while (length - 1 > ++i)
	{
		buff = str[i];
		str[i] = str[length - 1];
		str[length - 1] = buff;
		length--;
	}
	return (str);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, const char *src, size_t i)
{
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

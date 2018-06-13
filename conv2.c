/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maljean <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 02:08:15 by maljean           #+#    #+#             */
/*   Updated: 2018/06/12 17:22:33 by maljean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi(char *s, int i, int nb, int sign)
{
	if (!s)
		return (0);
	while (s[i] && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i++;
	if (s[i] == '-')
		sign = -1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = (nb * 10) + (s[i] - '0');
		i++;
	}
	return (sign * nb);
}

char	*ft_otoa(unsigned long int number, t_ops *ops)
{
	char				*print;
	unsigned int		i;
	unsigned long int	x;
	char				*tmp;

	x = number;
	ops->num += 1;
	i = 0;
	print = (char*)malloc(sizeof(char) * 24);
	tmp = print;
	if (number == 0 && !ops->pound && ops->p)
		return ("");
	if (number == 0)
	{
		print[i] = '0';
		i++;
	}
	while (number)
	{
		print[i] = (number % 8) + 48;
		number /= 8;
		i++;
	}
	print[i] = '\0';
	ft_strrev(print, -1, 0);
	(x != 0 && ops->pound) ? print = ft_strjoin("0", print) : 0;
	free(tmp);
	return (print);
}

char	*ft_ptoa(unsigned long int number, t_ops *ops)
{
	char	*print;
	int		i;
	char	*tmp;

	i = 0;
	print = (char*)malloc(sizeof(char) * 12);
	tmp = print;
	if (number == 0)
		print[i] = '0';
	while (number && ops->conv == 'p')
	{
		print[i++] = "0123456789abcdef"[number % 16];
		number /= 16;
	}
	print = ft_strrev(print, -1, 0);
	print = ft_strjoin("0x", print);
	free(tmp);
	return (print);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;

	i = ft_strlen(dest);
	while (*src)
		dest[i++] = *src++;
	dest[i] = '\0';
	return (dest);
}

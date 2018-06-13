/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maljean <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 02:03:41 by maljean           #+#    #+#             */
/*   Updated: 2018/06/12 17:19:01 by maljean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_zeros(char *s, t_ops *ops)
{
	char	*block;
	int		i;
	char	*tmp;

	i = -1;
	tmp = s;
	block = (char*)malloc(sizeof(char) * ops->prec + 1);
	if (!block)
		return (s);
	while (++i < ops->prec)
		block[i] = '0';
	block[i] = '\0';
	if (s[0] == '-')
	{
		s = ft_strjoin(block, &s[1]);
		s = ft_strjoin("-", s);
	}
	else
		s = ft_strjoin(block, s);
	ops->zero = 0;
	free(block);
	free(tmp);
	return (s);
}

char	*ft_spaces(char *s, t_ops *ops)
{
	char	block[ops->width + 1];
	int		i;
	char	edge[2];

	i = 0;
	edge[0] = s[0];
	edge[1] = '\0';
	if (ops->width < 1)
		return (s);
	while (i < ops->width)
	{
		block[i] = (ops->zero) ? '0' : ' ';
		i++;
	}
	block[i] = '\0';
	if ((edge[0] == '-' || edge[0] == '+') && ops->zero && ops->num)
	{
		s = ft_strjoin(block, &s[1]);
		s = ft_strjoin(edge, s);
	}
	else
		s = (ops->minus) ? ft_strjoin(s, block) : ft_strjoin(block, s);
	return (s);
}

char	*ft_chop(char *s, t_ops *ops, int i)
{
	char	*dest;

	dest = (char*)malloc(sizeof(char) * ops->prec + 1);
	while (++i < ops->prec)
		dest[i] = s[i];
	dest[i] = '\0';
	return (dest);
}

void	ft_apply_flags(char *s, t_ops *ops)
{
	if (!s)
	{
		ft_putstr("(null)", ops, -1);
		return ;
	}
	(s[0] == '-') ? ops->prec += 1 : 0;
	if (!ops->num)
		s = (ops->prec) ? ft_chop(s, ops, -1) : s;
	s = (ops->pound && ops->conv == 'x' && !ops->zero)
		? ft_strjoin("0x", s) : s;
	s = (ops->pound && ops->conv == 'X' && !ops->zero)
		? ft_strjoin("0X", s) : s;
	(ops->space && s[0] != '-') ? ops->width -= 1 : 0;
	ops->prec -= ft_strlen(s);
	(ops->plus && s[0] != '-') ? ops->width -= 1 : 0;
	s = (ops->num) ? ft_zeros(s, ops) : s;
	ops->width -= ft_strlen(s);
	s = (ops->plus && s[0] != '-') ? ft_strjoin("+", s) : s;
	s = ft_spaces(s, ops);
	s = (ops->pound && ops->conv == 'x' && ops->zero) ? ft_strjoin("0x", s) : s;
	s = (ops->pound && ops->conv == 'X' && ops->zero) ? ft_strjoin("0X", s) : s;
	s = (ops->space && s[0] != '-') ? ft_strjoin(" ", s) : s;
	ft_putstr(s, ops, -1);
}

void	ft_handle_it(t_ops *ops, va_list args)
{
	(ops->plus) ? ops->space = 0 : 0;
	(ops->conv == 'u' || ops->conv == 'U') ? ops->plus = 0 : 0;
	(ops->conv == 'u' || ops->conv == 'U') ? ops->space = 0 : 0;
	(ops->zero && ops->minus) ? ops->zero = 0 : 0;
	if (ops->conv == 's' && !ops->mod)
		ft_apply_flags(va_arg(args, char*), ops);
	else if (ops->conv == 'D')
		ft_apply_flags(ft_itoabase_umax(va_arg(args, long), 10, ops), ops);
	else if (ops->conv == 'S' ||
			(ops->conv == 's' && ft_strcmp("l", ops->mod) == 0))
		ft_putwstr(va_arg(args, wchar_t*), ops, -1);
	else if (ops->conv == 'C')
		ft_putwstr((ft_wchrtostr(va_arg(args, wchar_t))), ops, -1);
	else if (ops->conv == 'c')
		ft_putchar(va_arg(args, int), ops);
	else if (ops->conv == 'o' || ops->conv == 'O')
		ft_apply_flags(ft_otoa(va_arg(args, unsigned int), ops), ops);
	else if (ops->conv == 'p')
		ft_apply_flags(ft_ptoa(va_arg(args, unsigned long int), ops), ops);
	else if (ops->conv == 'd' || ops->conv == 'i')
		ft_apply_flags(ft_mod_cast(args, ops, 10), ops);
	else if (ops->conv == 'x' || ops->conv == 'X')
		ft_apply_flags(ft_hex_cast(args, ops, 16), ops);
	else if (ops->conv == 'u' || ops->conv == 'U')
		ft_apply_flags(ft_itoabase_umax(va_arg(args, intmax_t), 10, ops), ops);
}

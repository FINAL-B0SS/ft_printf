/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maljean <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 02:03:41 by maljean           #+#    #+#             */
/*   Updated: 2018/06/07 19:16:04 by maljean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_zeros(char *s, t_ops *ops)
{
	char	*block;
	int		i;

	i = -1;
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

int	print_unicode(va_list list, t_ops *ops)
{
	wchar_t	*fake_wide;
	wchar_t *wide;
	int	len;
	char	org;
	int	i;

	i = 0;
	len = 0;
	org = 0;
	wide = va_arg(list, wchar_t*);
	fake_wide = NULL;
	if (len == 1)
		fake_wide[0] = org;
	else if (len == 2)
	{
		fake_wide[0] = ((org >> 6) | 0xC0);
		fake_wide[1] = ((org & 0x3f) | 0x80);
	}
	else if (len == 3)
	{
		fake_wide[0] = ((org >> 12) | 0xE0);
		fake_wide[1] = (((org >> 6) & 0x3f) | 0x80);
		fake_wide[2] = ((org & 0x3f) | 0x80);
	}
	else if (len == 4)
	{
		fake_wide[0] = ((org >> 18) | 0xf0);
		fake_wide[1] = (((org >> 12) & 0x3f) | 0x80);
		fake_wide[2] = (((org >> 6) & 0x3f) | 0x80);
		fake_wide[3] = ((org & 0x3f) | 0x80);
	}
	ft_putwstr(wide, ops);
	return (len);
}

void	ft_handle_it(t_ops *ops, va_list args)
{
	(ops->plus) ? ops->space = 0 : 0;
	(ops->conv == 'u' || ops->conv == 'U') ? ops->plus = 0 : 0;
	(ops->conv == 'u' || ops->conv == 'U') ? ops->space = 0 : 0;
	(ops->zero && ops->minus) ? ops->zero = 0 : 0;
	if (ops->conv == 's')
		ft_apply_flags(va_arg(args, char*), ops);
	else if (ops->conv == 'D')
		ft_apply_flags(ft_itoabase_umax(va_arg(args, long), 10, ops), ops);
	else if (ops->conv == 'S' || (ops->conv == 'S' && ops->mod[0] == 'l'))
		print_unicode(args, ops);
	else if (ops->conv == 'C')
		ft_putwstr((ft_wchrtostr(va_arg(args, wchar_t))), ops);
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

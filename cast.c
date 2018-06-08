/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maljean <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 02:12:37 by maljean           #+#    #+#             */
/*   Updated: 2018/06/07 23:08:55 by maljean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_ops(t_ops *ops)
{
	ops->bytes = 0;
	ops->num = 0;
	ops->space = 0;
	ops->minus = 0;
	ops->pound = 0;
	ops->zero = 0;
	ops->plus = 0;
	ops->width = 0;
	ops->prec = 0;
	ops->conv = 0;
	ops->mod = 0;
	ops->p = 0;
	ops->c = 0;
}

char	*ft_mod_cast(va_list args, t_ops *ops, int base)
{
	ops->num += 1;
	if (!ops->mod)
		return (ft_itoa((va_arg(args, ssize_t)), ops, 1, 0));
	else if (!ft_strcmp(ops->mod, "z"))
		return (ft_itoa_smax(va_arg(args, ssize_t)));
	else if (!ft_strcmp(ops->mod, "j"))
		return (ft_itoa_smax(va_arg(args, intmax_t)));
	else if (!ft_strcmp(ops->mod, "ll"))
		return (ft_itoa_smax(va_arg(args, long long)));
	else if (!ft_strcmp(ops->mod, "l"))
		return (ft_itoa_smax(va_arg(args, long)));
	else if (!ft_strcmp(ops->mod, "hh"))
		return (ft_itoa_smax((char)va_arg(args, int)));
	else if (!ft_strcmp(ops->mod, "h"))
		return (ft_itoa((short)va_arg(args, int), ops, 1, 0));
	else
		return (ft_itoabase_umax(va_arg(args, intmax_t), base, ops));
}

char	*ft_hex_cast(va_list args, t_ops *ops, int base)
{
	ops->num += 1;
	if (!ops->mod)
		return (ft_itoabase_umax((va_arg(args, unsigned int)), base, ops));
	else if (!ft_strcmp(ops->mod, "z"))
		return (ft_itoabase_umax(va_arg(args, ssize_t), base, ops));
	else if (!ft_strcmp(ops->mod, "j"))
		return (ft_itoabase_umax(va_arg(args, intmax_t), base, ops));
	else if (!ft_strcmp(ops->mod, "ll"))
		return (ft_itoabase_umax(va_arg(args, long long), base, ops));
	else if (!ft_strcmp(ops->mod, "l"))
		return (ft_itoabase_umax(va_arg(args, long), base, ops));
	else if (!ft_strcmp(ops->mod, "hh"))
		return (ft_itoabase_umax((char)va_arg(args, int), base, ops));
	else if (!ft_strcmp(ops->mod, "h"))
		return (ft_itoabase_umax((short)va_arg(args, int), base, ops));
	else
		return (ft_itoabase_umax(va_arg(args, intmax_t), base, ops));
}

void	ft_putwstr(wchar_t *ws, t_ops *ops, int i)
{
	ops->width -= (ops->prec -ft_wstrlen(ws));
	ops->minus ? ops->zero = 0 : 0;
	if (ops->width && !ops->minus)
		while (ops->width--)
			ops->zero ? write(1, "0", 1) : write(1, " ", 1);
	while (ws[++i])
	{
		if (ops->prec && ops->prec < ft_wstrlen(ws))
		{
			while (ops->prec--)
				ft_putchar(ws[i], ops);
			break ;
		}
		ft_putchar(ws[i], ops);
		ops->bytes += 1;
	}
	if (ops->width && ops->minus)
		while (ops->width--)
			ops->zero ? write(1, "0", 1) : write(1, " ", 1);
}

wchar_t	*ft_wchrtostr(wchar_t wchar)
{
	wchar_t	*wstr;

	wstr = (wchar_t *)malloc(sizeof(wchar) * 2);
	if (wstr)
	{
		wstr[0] = wchar;
		wstr[1] = L'\0';
	}
	return (wstr);
}

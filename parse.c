/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maljean <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 02:01:57 by maljean           #+#    #+#             */
/*   Updated: 2018/06/06 02:31:16 by maljean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_conv_check(int i, char *s, char c)
{
	while (s[++i])
		if (c == s[i])
			return (1);
	return (0);
}

int	ft_mod_check(char *s, int *i, t_ops *ops)
{
	(s[*i] == 'h' && s[*i + 1] == 'h') ? ops->mod = "hh" : 0;
	(s[*i] == 'h' && s[*i + 1] != 'h') ? ops->mod = "h" : 0;
	(s[*i] == 'l' && s[*i + 1] != 'l') ? ops->mod = "l" : 0;
	(s[*i] == 'l' && s[*i + 1] == 'l') ? ops->mod = "ll" : 0;
	(s[*i] == 'j') ? ops->mod = "j" : 0;
	(s[*i] == 'z') ? ops->mod = "z" : 0;
	if (ops->mod)
	{
		*i += ft_strlen(ops->mod);
		if (ft_conv_check(-1, "sSpdDioOuUxXcC", s[*i]))
			return (1);
		else
			return (0);
	}
	return (1);
}

void	ft_flag_save(char *s, t_ops *ops, int *i)
{
	while (s[*i] && (s[*i] == '#' || s[*i] == '0' ||
				s[*i] == '-' || s[*i] == '+' || s[*i] == ' '))
	{
		(s[*i] == '0') ? ops->zero += 1 : 0;
		(s[*i] == '-') ? ops->minus += 1 : 0;
		(s[*i] == '+') ? ops->plus += 1 : 0;
		(s[*i] == '#') ? ops->pound += 1 : 0;
		(s[*i] == ' ') ? ops->space += 1 : 0;
		*i += 1;
	}
}

void	ft_prec_width_parse(char *s, int *i, t_ops *ops, va_list args)
{
	if (s[*i] && (((s[*i] > '0' && s[*i] <= '9')) || (s[*i] == '*' && s[*i - 1] != '*')))
	{
		if (s[*i] == '*' && s[*i - 1] != '*')
		{
			ops->width = va_arg(args, int);
			*i += 1;
		}
		else
		{
			ops->width = (ft_atoi(&s[*i], 0, 0, 1));
			*i += ft_nbrlen(ft_atoi(&s[*i], 0, 0, 1), 0);
		}
	}
	if (s[*i] && (s[*i] == '.'))
	{
		*i += 1;
		ops->p += 1;
		if (s[*i] == '*')
			ops->prec = va_arg(args, int);
		else if (s[*i] && s[*i] >= '0' && s[*i] <= '9')
			ops->prec = (ft_atoi(&s[*i], 0, 0, 1));
		while ((s[*i] >= '0' && s[*i]<= '9') || s[*i] == '*')
			*i += 1;
	}
}

int	ft_parse(char *s, int *i, t_ops *ops, va_list args)
{
	*i += 1;
	ft_flag_save(s, ops, i);
	ft_prec_width_parse(s, i, ops, args);
	if (ft_mod_check(s, i, ops) == -1)
		return (0);
	if (ft_conv_check(-1, "sSpdDioOuUxXcC", s[*i]))
	{
		ops->c += 1;
		ops->conv = s[*i];
	}
	if (ops->p <= 1 && ops->c == 1 ? 1 : 0)
		return (1);
	if (ops->zero)
		ft_putstr(ft_zeros("", ops), ops, -1);
	if (ops->width)
	{
		ops->width -= 1;
		(ops->minus) ? ft_putchar(s[*i], ops) : 0;
		(ops->minus) ? *i += 1 : 0;
		ft_putstr(ft_spaces("", ops), ops, -1);
	}
	return (0);
}

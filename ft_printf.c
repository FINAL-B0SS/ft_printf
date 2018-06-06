/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maljean <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 23:48:08 by maljean           #+#    #+#             */
/*   Updated: 2018/06/06 01:22:36 by maljean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <wchar.h>
#include <limits.h>
#include <locale.h>

typedef struct	s_ops
{
	int		num;
	int		space;
	int		minus;
	int		pound;
	int		plus;
	int		zero;
	int		width;
	int		prec;
	char	conv;
	char	*mod;
	int		f;
	int		w;
	int		p;
	int		c;
	int		m;
	int		data;
	int		bytes;
}				t_ops;

void	ft_init_ops(t_ops *ops)
{
	ops->bytes = 0;
	ops->num = 0;
	ops->data = 0;
	ops->space = 0;
	ops->minus = 0;
	ops->pound = 0;
	ops->zero = 0;
	ops->plus = 0;
	ops->width = 0;
	ops->prec = 0;
	ops->conv = 0;
	ops->mod = 0;
	ops->f = 0;
	ops->w = 0;
	ops->p = 0;
	ops->c = 0;
	ops->m = 0;
}

int	ft_nbrlen(int n, int i)
{
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

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

int	ft_strlen(char *s, int i)
{
	while (s[++i]);
	return (i);
}

char	*ft_strcpy(char *dest, const char *src, size_t i)
{
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;

	i = ft_strlen(dest, -1);
	while (*src)
		dest[i++] = *src++;
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char *)malloc(ft_strlen((char *)s1, -1) +
					ft_strlen((char *)s2, -1)), -1))
		return (NULL);
	str = ft_strcpy(str, s1, -1);
	str = ft_strcat(str, s2);
	return (str);
}

char	*ft_strdup(char *s1, int i)
{
	int		s1_len;
	char	*str_copy;

	s1_len = ft_strlen(s1, -1);
	str_copy = malloc(sizeof(*str_copy) * (s1_len + 1));
	if (str_copy)
	{
		while (s1[++i] != '\0')
			str_copy[i] = s1[i];
		str_copy[i] = '\0';
	}
	return (str_copy);
}

size_t	ft_wstrlen(const wchar_t *s, size_t len)
{
	while (s[++len] != L'\0');
	return (len);
}

int	ft_atoi(char *s, int i, int nb, int sign)
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

char	*ft_itoa(int nbr, t_ops *ops)
{
	int		length;
	int		sign;
	char	*str;

	sign = nbr;
	length = 1;
	if (nbr == 0 && ops->p)
		return ("");
	while (sign /= 10)
		length++;
	sign = nbr < 0 ? 1 : 0;
	length = nbr < 0 ? length += 1 : length;
	str = (char*)malloc(sizeof(char) * length + 1);
	if (nbr == -2147483648)
		return (str = ft_strdup("-2147483648", -1));
	if (!str)
		return (NULL);
	(sign) ? str[0] = '-' : 0;
	nbr = nbr < 0 ? nbr *= -1 : nbr;
	while (--length >= sign)
	{
		str[length] = (nbr >= 10) ? (nbr % 10) + 48 : nbr + 48;
		nbr /= 10;
	}
	str[ft_strlen(str, -1)] = '\0';
	return (str);
}

static int	get_unumlen(size_t num, int base)
{
	int	i;

	i = 1;
	while (num /= base)
		i++;
	return (i);
}

char	*ft_itoabase_umax(size_t num, int base, t_ops *ops)
{
	char			*str;
	int				len;
	char			*basestr;

	basestr = ft_strdup("0123456789abcdef", -1);
	ops->num += 1;
	len = get_unumlen(num, base);
	num == 0 ? ops->pound = 0 : 0;
	if (num == 0 && ops->p)
		return ("");
	if (!(str = (char *)malloc(sizeof(*str) * len + 1)))
	{
		return (NULL);
	}
	str[len] = '\0';
	str[--len] = basestr[num % base];
	while (num /= base)
		str[--len] = basestr[num % base];
	len = -1;
	if (ops->conv == 'X')
		while (str[++len])
			(str[len] >= 'a' && str[len] <= 'z') ? str[len] -= 32 : 0;
	free(basestr);
	return (str);
}

static	int	get_snumlen(intmax_t num)
{
	int	i;

	i = 1;
	while (num /= 10)
		i++;
	return (i);
}

char		*ft_itoa_smax(intmax_t num)
{
	char		*str;
	int			len;
	uintmax_t	tmp;

	len = get_snumlen(num);
	tmp = num;
	if (num < 0)
	{
		tmp = -num;
		len++;
	}
	if (!(str = (char *)malloc(sizeof(*str) * len)))
		return (NULL);
	str[len] = '\0';
	str[--len] = tmp % 10 + '0';
	while (tmp /= 10)
		str[--len] = tmp % 10 + '0';
	(num < 0) ? str[0] = '-' : 0;
	return (str);
}
char	*ft_otoa(unsigned long int number, t_ops *ops)
{
	char				*print;
	unsigned int		i;
	unsigned long int	x;

	x = number;
	ops->num += 1;
	i = 0;
	print = (char*)malloc(sizeof(char) * 24);
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
	return (print);
}

char	*ft_ptoa(unsigned long int number, t_ops *ops)
{
	char	*print;
	int		i;

	i = 0;
	print = (char*)malloc(sizeof(char) * 12);
	if (number == 0)
		print[i] = '0';
	while (number && ops->conv == 'p')
	{
		print[i++] = "0123456789abcdef"[number % 16];
		number /= 16;
	}
	print = ft_strrev(print, -1, 0);
	print = ft_strjoin("0x", print);
	return (print);
}

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

char	*ft_chop(char *s, t_ops *ops)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char*)malloc(sizeof(char) * ops->prec + 1);
	while (i < ops->prec)
	{
		dest[i] = s[i];
		i++;
	}
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
		s = (ops->prec) ? ft_chop(s, ops) : s;
	s = (ops->pound && ops->conv == 'x' && !ops->zero) ? ft_strjoin("0x", s) : s;
	s = (ops->pound && ops->conv == 'X' && !ops->zero) ? ft_strjoin("0X", s) : s;
	(ops->space && s[0] != '-') ? ops->width -= 1 : 0;
	ops->prec -= ft_strlen(s, -1);
	(ops->plus && s[0] != '-') ? ops->width -= 1 : 0;
	s = (ops->num) ? ft_zeros(s, ops) : s;
	ops->width -= ft_strlen(s, -1);
	s = (ops->plus && s[0] != '-') ? ft_strjoin("+", s) : s;
	s = ft_spaces(s, ops);
	s = (ops->pound && ops->conv == 'x' && ops->zero) ? ft_strjoin("0x", s) : s;
	s = (ops->pound && ops->conv == 'X' && ops->zero) ? ft_strjoin("0X", s) : s;
	s = (ops->space && s[0] != '-') ? ft_strjoin(" ", s) : s;
	ft_putstr(s, ops, -1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
		s1++ && s2++;
	return (*(unsigned char*)s1) - *((unsigned char*)s2);
}

char	*ft_mod_cast(va_list args, t_ops *ops, int base)
{
	ops->num += 1;
	if (!ops->mod)
		return (ft_itoa((va_arg(args, ssize_t)), ops));
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
		return (ft_itoa((short)va_arg(args, int), ops));
	else
		return (ft_itoabase_umax(va_arg(args, intmax_t), base, ops));
}

char	*ft_hex_cast(va_list args, t_ops *ops, int base)
{
	ops->num += 1;
	if (!ops->mod)
		return (ft_itoabase_umax((va_arg(args, unsigned int)), base, ops));
	else if (!ft_strcmp(ops->mod, "z"))
		return (ft_itoabase_umax(va_arg(args, ssize_t), base,  ops));
	else if (!ft_strcmp(ops->mod, "j"))
		return (ft_itoabase_umax(va_arg(args, intmax_t), base, ops));
	else if (!ft_strcmp(ops->mod, "ll"))
		return (ft_itoabase_umax(va_arg(args, long long), base, ops));
	else if (!ft_strcmp(ops->mod, "l"))
		return (ft_itoabase_umax(va_arg(args, long), base, ops));
	else if (!ft_strcmp(ops->mod, "hh"))
		return (ft_itoabase_umax((char)va_arg(args, int), base, ops));
	else if (!ft_strcmp(ops->mod, "h"))
		return (ft_itoabase_umax((short)va_arg(args, int), base,  ops));
	else
		return (ft_itoabase_umax(va_arg(args, intmax_t), base, ops));
}

void	ft_putwchar(wchar_t a)
{
	write(1, &a, 1);
}

void	ft_putwstr(wchar_t *ws, t_ops *ops)
{
	int i;

	i = 0;
	while (ws[i] != '\0')
	{
		ft_putwchar(ws[i]);
		i++;
		ops->bytes += 1;
	}
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

void	ft_default(t_ops *ops)
{
	(ops->plus) ? ops->space = 0 : 0;
	(ops->conv == 'u' || ops->conv == 'U') ? ops->plus = 0 : 0;
	(ops->conv == 'u' || ops->conv == 'U') ? ops->space = 0 : 0;
	(ops->zero && ops->minus) ? ops->zero = 0 : 0;

}

void	ft_handle_it(t_ops *ops, va_list args)
{
	ft_default(ops);
	if (ops->conv == 's')
		ft_apply_flags(va_arg(args, char*), ops);
	else if (ops->conv == 'D')
		ft_apply_flags(ft_itoabase_umax(va_arg(args, long), 10, ops), ops);
	else if (ops->conv == 'S' || (ops->conv == 'S' && ops->mod[0] == 'l'))
		ft_putwstr(va_arg(args, wchar_t*), ops);
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
		*i += ft_strlen(ops->mod, -1);
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
		{
			ops->prec = va_arg(args, int);
			*i += 1;
		}
		else if (s[*i] && s[*i] >= '0' && s[*i] <= '9')
			ops->prec = (ft_atoi(&s[*i], 0, 0, 1));
		while (s[*i] >= '0' && s[*i]<= '9')
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
	if (ops->w <= 1 && ops->p <= 1 && ops->m <= 1 && ops->c == 1 ? 1 : 0)
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

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;
	int			bytes;
	t_ops		ops;

	i = -1;
	bytes = 0;
	va_start(args, format);
	if (!format)
		return (0);
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
		else if (i < ft_strlen((char*)format, -1))
			ft_putchar(format[i], &ops);
		bytes += ops.bytes;
	}
	va_end(args);
	return (bytes);
}

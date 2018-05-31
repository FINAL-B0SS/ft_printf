/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maljean <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 23:48:08 by maljean           #+#    #+#             */
/*   Updated: 2018/05/30 21:49:32 by maljean          ###   ########.fr       */
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
}				t_ops;

void	ft_init_ops(t_ops *ops)
{
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

int	ft_nbrlen(int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		return ;
	}
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

char	*ft_strrev(char *str)
{
	int		i;
	int		length;
	char	buff;

	i = 0;
	length = 0;
	while (str[length])
		length++;
	while (length - 1 > i)
	{
		buff = str[i];
		str[i] = str[length - 1];
		str[length - 1] = buff;
		length--;
		i++;
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

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char *)malloc(ft_strlen((char *)s1) +
					ft_strlen((char *)s2) + 1)))
		return (NULL);
	str = ft_strcpy(str, s1);
	str = ft_strcat(str, s2);
	return (str);
}

char	*ft_strdup(char *s1)
{
	int		s1_len;
	char	*str_copy;
	int		i;

	s1_len = ft_strlen(s1);
	str_copy = malloc(sizeof(*str_copy) * (s1_len + 1));
	if (str_copy)
	{
		i = 0;
		while (s1[i] != '\0')
		{
			str_copy[i] = s1[i];
			i++;
		}
		str_copy[i] = '\0';
	}
	return (str_copy);
}

size_t	ft_wstrlen(const wchar_t *s)
{
	size_t len;

	len = 0;
	while (s[len] != L'\0')
	{
		len++;
	}
	return (len);
}

wchar_t	*ft_wstrdup(const wchar_t *wstr)
{
	size_t	len;
	wchar_t	*wstr_copy;
	int		i;

	len = ft_wstrlen(wstr);
	wstr_copy = malloc(sizeof(*wstr_copy) * (len + 1));
	if (wstr_copy)
	{
		i = 0;
		while (wstr[i] != L'\0')
		{
			wstr_copy[i] = wstr[i];
			i++;
		}
		wstr_copy[i] = L'\0';
	}
	return (wstr_copy);
}

int	ft_atoi(char *s)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
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
	ops->num += 1;
	while (sign /= 10)
		length++;
	sign = nbr < 0 ? 1 : 0;
	length = nbr < 0 ? length += 1 : length;
	str = (char*)malloc(sizeof(char) * length + 1);
	if (nbr == -2147483648)
		return (str = ft_strdup("-2147483648"));
	if (!str)
		return (NULL);
	(sign) ? str[0] = '-' : 0;
	nbr = nbr < 0 ? nbr *= -1 : nbr;
	while (--length >= sign)
	{
		str[length] = (nbr >= 10) ? (nbr % 10) + 48 : nbr + 48;
		nbr /= 10;
	}
	str[ft_strlen(str)] = '\0';
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
	int				i;

	basestr = ft_strdup("0123456789abcdef");
	len = get_unumlen(num, base);
	ops->num += 1;
	if (!(str = (char *)malloc(sizeof(*str) * len + 1)))
	{
		return (NULL);
	}
	str[len] = '\0';
	str[--len] = basestr[num % base];
	while (num /= base)
	{
		str[--len] = basestr[num % base];
	}
	free(basestr);
	return (str);
}

char	*ft_otoa(unsigned long int number, t_ops *ops)
{
	char				*print;
	unsigned int		i;
	unsigned long int	x;

	x = number;
	i = 0;
	ops->num += 1;
	print = (char*)malloc(sizeof(char) * 24);
	if (number < i)
		return ("errno: Unsigned Only!");
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
	ft_strrev(print);
	(x != 0 && ops->pound) ? print = ft_strjoin("0", print) : 0;
	return (print);
}

char	*ft_ptoa(unsigned long int number, t_ops *ops)
{
	char	*print;
	int		i;

	i = 0;
	ops->num += 1;
	print = (char*)malloc(sizeof(char) * 12);
	if (number == 0)
		print[i] = '0';
	while (number && ops->conv == 'p')
	{
		print[i++] = "0123456789abcdef"[number % 16];
		number /= 16;
	}
	print = ft_strrev(print);
	print = ft_strjoin("0x", print);
	return (print);
}

char	*ft_htoa(unsigned long int number, t_ops *ops)
{
	char	*print;
	int		i;

	i = 0;
	print = (char*)malloc(sizeof(char) * 18);
	ops->num += 1;
	if (number == 0)
		print[i] = '0';
	while (number && ops->conv == 'x')
	{
		print[i++] = "0123456789abcdef"[number % 16];
		number /= 16;
	}
	while (number && ops->conv == 'X')
	{
		print[i++] = "0123456789ABCDEF"[number % 16];
		number /= 16;
	}
	ft_strrev(print);
	if (ops->pound && ops->conv == 'x')
		print = ft_strjoin("0x", print);
	else if (ops->pound && ops->conv == 'X')
		print = ft_strjoin("0X", print);
	return (print);
}

char	*ft_zeros(char *s, t_ops *ops)
{
	char	*block;
	int		i;

	i = 0;
	block = (char*)malloc(sizeof(char) * ops->prec + 1);
	if (!block)
		return (s);
	while (i < ops->prec)
	{
		block[i] = '0';
		i++;
	}
	block[i] = '\0';
	if (s[0] == '-')
	{
		s = ft_strjoin(block, &s[1]);
		s = ft_strjoin("-", s);
	}
	else
		s = ft_strjoin(block, s);
	ops->zero = 0;
	return (s);
}

char	*ft_spaces(char *s, t_ops *ops)
{
	char	*block;
	int		i;

	i = 0;
	block = (char*)malloc(sizeof(char) * ops->width + 1);
	if (!block)
		return (s);
	while (i < ops->width)
	{
		block[i] = (ops->zero && ops->prec) ? '0' : ' ';
		i++;
	}
	block[i] = '\0';
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
		write(1, "(null)", 6);
		return ;
	}
	if (ops->num)
	{
		(ops->space && s[0] != '-') ? ops->width -= 1 : 0;
		ops->prec -= ft_strlen(s);
		(ops->plus) ? ops->width -= 1 : 0;
		s = ft_zeros(s, ops);
		ops->width -= ft_strlen(s);
		s = ft_spaces(s, ops);
		s = (ops->space && s[0] != '-') ? ft_strjoin(" ", s) : s;
		s = (ops->plus && s[0] != '-') ? ft_strjoin("+", s) : s;
	}
	else
	{
		s = (ops->prec) ? ft_chop(s, ops) : s;
		ops->width -= ft_strlen(s);
		s = ft_spaces(s, ops);
	}
	ft_putstr(s);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
		s1++ && s2++;
	return (*(unsigned char*)s1) - *((unsigned char*)s2);
}

char	*ft_mod_cast(va_list args, t_ops *ops, int base)
{
	char	*s;

	if (!ops->mod)
		s = ft_itoa((va_arg(args, ssize_t)), ops);
	else if (ft_strcmp(ops->mod, "l") && ops->conv == 'd')
		s = ft_itoabase_umax(va_arg(args, long), base, ops);
	else if (ft_strcmp(ops->mod, "j") || ft_strcmp(ops->mod, "z"))
		s = ft_itoabase_umax(va_arg(args, intmax_t), base, ops);
	else if (ft_strcmp(ops->mod, "ll"))
		s = ft_itoabase_umax(va_arg(args, long long), base, ops);
	else if (ft_strcmp(ops->mod, "l"))
		s = ft_itoabase_umax(va_arg(args, long), base, ops);
	else if (ft_strcmp(ops->mod, "hh"))
		s = ft_itoabase_umax((char)va_arg(args, int), base, ops);
	else if (ft_strcmp(ops->mod, "h"))
		s = ft_itoabase_umax((short)va_arg(args, int), base, ops);
	else
		s = ft_itoabase_umax(va_arg(args, intmax_t), base, ops);
	return (s);
}

void	ft_putwchar(wchar_t a)
{
	write(1, &a, 1);
}

int	ft_putwstr(wchar_t *ws)
{
	int i;

	i = 0;
	while (ws[i] != '\0')
	{
		ft_putwchar(ws[i]);
		i++;
	}
	return (i);
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

void	ft_handle_it(t_ops *ops, va_list args)
{
	if (ops->conv == 's')
		ft_apply_flags(va_arg(args, char*), ops);
	else if (ops->conv == 'S' || (ops->conv == 'S' && ops->mod[0] == 'l'))
		ft_putwstr(va_arg(args, wchar_t*));
	else if (ops->conv == 'C')
		ft_putwstr((ft_wchrtostr(va_arg(args, wchar_t))));
	else if (ops->conv == 'c')
		ft_putchar(va_arg(args, int));
	else if (ops->conv == 'o' || ops->conv == 'O')
		ft_apply_flags(ft_otoa(va_arg(args, unsigned int), ops), ops);
	else if (ops->conv == 'p')
		ft_apply_flags(ft_ptoa(va_arg(args, unsigned long int), ops), ops);
	else if (ops->conv == 'd' || ops->conv == 'i' || ops->conv == 'D')
		ft_apply_flags(ft_mod_cast(args, ops, 10), ops);
	else if (ops->conv == 'x' || ops->conv == 'X')
		ft_apply_flags(ft_htoa(va_arg(args, unsigned int), ops), ops);
	else if (ops->conv == 'u')
		ft_putstr(ft_itoabase_umax(va_arg(args, intmax_t), 10, ops));
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
		*i += ft_strlen(ops->mod);
		if (ft_conv_check(-1, "sSpdDioOuUxXcC", s[*i]))
		{
			ops->m += 1;
			return (1);
		}
		else
			return (-1);
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

int	ft_parse(char *s, int *i, t_ops *ops)
{
	*i += 1;
	ft_flag_save(s, ops, i);
	if (s[*i] && ((s[*i] > '0' && s[*i] <= '9') && s[*i] != '*'))
	{
		ops->w += 1;
		ops->width = (ft_atoi(&s[*i]));
		*i += ft_nbrlen(ft_atoi(&s[*i]));
	}
	if (s[*i] && (s[*i] == '.') && s[*i] != '*')
	{
		*i += 1;
		ops->p += 1;
		ops->prec = (ft_atoi(&s[*i]));
		*i += ft_nbrlen(ft_atoi(&s[*i]));
	}
	if (ft_mod_check(s, i, ops) == -1)
		return (0);
	while (s[*i])
	{
		if (ft_conv_check(-1, "sSpdDioOuUxXcC", s[*i]))
		{
			ops->c += 1;
			ops->conv = s[*i];
			break ;
		}
		*i += 1;
	}
	return ((ops->w <= 1 && ops->p <= 1 && ops->m <= 1 && ops->c == 1) ? 1 : 0);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			i;
	t_ops		ops;

	i = -1;
	va_start(args, format);
	if (!format)
		return (0);
	while (format[++i])
	{
		if (format[i] == '%' && format[i + 1] == '%')
		{
			write(1, "%", 1);
			i += 1;
		}
		else if (format[i] == '%')
		{
			ft_init_ops(&ops);
			(ft_parse((char*)format, &i, &ops)) ? ft_handle_it(&ops, args) : 0;
		}
		else
			write(1, &format[i], 1);
	}
	va_end(args);
	return (1);
}
/*
int main()
{
	wchar_t a [3] = L"@@";
//	ft_printf("%qqqqqqq\n", "test");
//	ft_printf("Handling %%%%: %%\n");
//	ft_printf("Octal: %#o\n", 0);
//	ft_printf("String: % s\n", "Hello World!");
//	ft_printf("Integer: %d\n", -2147483648);
//	ft_printf("Lowercase Hex: %#x\n", 42);
//	ft_printf("Upercase Hex: %#X\n", 42);
//	printf("Ascii Charcter: %c\n", '*');
//	ft_printf("Unsigned int: %030u\n", 214783649);
//	ft_printf("Basic text: Test test 123\n");
//	printf("\t-----------------Mine----------------\n");
//	printf("%-5.3s\n", "LYDI");
//	printf("% 4.5i\n", 42);
//	printf("%04.5i\n", 42);
//	printf("%04.3i\n", 42);
//	printf("%04.2i\n", 42);
///	printf("%  i\n", 42);
//	printf("% i\n", -42);
//	printf("% 4i\n", 42);
//	printf("%-i\n", 42);
//	printf("%-ld\n", -2147483648);
//	printf("%-i\n",-42);
//	printf("%-4d\n", 42);
//	printf("%-5d\n", -42);
//	printf("%-4i\n", 42);
//	printf("\t---------------Theirs------------------\n");
//	ft_printf("%-5.3s\n", "LYDI");
//	ft_printf("% 4.5i\n", 42);
//	ft_printf("%04.5i\n", 42);
//	ft_printf("%04.3i\n", 42);
//	ft_printf("%04.2i\n", 42);
//	ft_printf("%  i\n", 42);
//	ft_printf("% i\n", -42);
//	ft_printf("% 4i\n", 42);
//	ft_printf("%-i\n", 42);
//	ft_printf("%-d\n", -2147483648);
//	ft_printf("%-i\n",-42);
//	ft_printf("%-4d\n", 42);
//	ft_printf("%-5d\n", -42);
//	ft_printf("%-4i\n", 42);
	ft_printf("%ls\n", a);
	ft_printf("%S\n", a);
	return (0);
}*/

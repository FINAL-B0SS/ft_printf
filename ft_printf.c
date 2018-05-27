#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <wchar.h>
#include <limits.h>
#include <locale.h>

typedef struct	s_options
{
	int		space;
	int		minus;
	int		pound;
	int		plus;
	int		zero;
	int		width;
	int		precision;
	char	conversion;
	char	*modifier;
	int		f;
	int		w;
	int		p;
	int		c;
	int		m;
	int		data;
	int		negative;
}		t_options;

void	ft_init_options(t_options *options)
{
	options->data = 0;
	options->space = 0;
	options->minus = 0;
	options->pound = 0;
	options->zero = 0;
	options->plus = 0;
	options->width = 0;
	options->precision = 0;
	options->conversion = 0;
	options->modifier = 0;
	options->f = 0;
	options->w = 0;
	options->p = 0;
	options->c = 0;
	options->m = 0;
	options->negative = 0;
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

void	ft_putstr(char *s, t_options *options)
{
	int	i;

	i = 0;
	if (options->precision)
	{
		while (options->precision && s[i])
		{
			write(1, &s[i], 1);
			options->precision -= 1;
			i++;
		}
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

char	*ft_itoa(int nbr)
{
	int		length;
	int		sign;
	char	*str;

	sign = nbr;
	length = 1;
	while (sign /= 10)
		length++;
	sign = nbr < 0 ? 1 : 0;
	length = nbr < 0 ? length += 1 : length;
	str = (char*)malloc(sizeof(char) * length + 1);
	if (!str)
		return (NULL);
	if (sign)
		str[0] = '-';
	nbr = nbr < 0 ? nbr *= -1 : nbr;
	while (--length >= sign)
	{
		str[length] = (nbr >= 10) ? (nbr % 10) + 48 : nbr + 48;
		nbr /= 10;
	}
	str[ft_strlen(str)] = '\0';
	return (str);
}

int	ft_modifier_double_check(char *s, int *i, t_options *options)
{
	*i += ft_strlen(options->modifier);	
	if (s[*i] && (s[*i] == 's' || s[*i] == 'S' || s[*i] == 'p' || s[*i] == 'd' || s[*i] == 'D' || s[*i] == 'i' || s[*i] == 'C' || s[*i] == 'o' || s[*i] == 'O' || s[*i] == 'u' || s[*i] == 'U' || s[*i] == 'x' || s[*i] == 'X' || s[*i] == 'c'))
	{
		options->m += 1;
		return (1);
	}
	else
		return (-1);
}

int	ft_modifier_check(char *s, int *i, t_options *options)
{
	if (s[*i] == 'h' && s[*i + 1] == 'h')
	{
		options->modifier = "hh";
		return (ft_modifier_double_check(s, i, options));
	}
	if (s[*i] == 'h' && s[*i + 1] != 'h')
	{
		options->modifier = "h";
		return (ft_modifier_double_check(s, i, options));
	}
	if (s[*i] == 'l' && s[*i + 1] != 'l')
	{
		options->modifier = "l";
		return (ft_modifier_double_check(s, i, options));
	}
	if (s[*i] == 'l' && s[*i + 1] == 'l')
	{
		options->modifier = "ll";
		return (ft_modifier_double_check(s, i, options));
	}
	if (s[*i] == 'j')
	{
		options->modifier = "j";
		return (ft_modifier_double_check(s, i, options));
	}
	if (s[*i] == 'z')
	{
		options->modifier = "z";
		return (ft_modifier_double_check(s, i, options));
	}
	return (2);
}

int	ft_default_to(t_options *options)
{
/*	(options->space && options->plus) ? options->space = 0 : 0;
	(options->zero && options->minus) ? options->zero = 0 : 0;
	(options->plus && options->conversion == 's') ? options->plus = 0 : 0;
	(options->space && options->conversion == 's') ? options->space = 0 : 0;
	(options-> plus && options->conversion == 'c') ? options->plus = 0 : 0;
	(options->space && options->conversion == 'c') ? options->space = 0 : 0;
//	(options->zero && (options->precision || options->conversion == 'd')) ? options->zero = 0 : 0;
//	(options->pound && options->conversion == 'i') ? options->zero = 0 : 0;
	(options->plus && options->conversion == 'o') ? options->plus = 0 : 0;
	(options->space && options->conversion == 'o') ? options->space = 0 : 0;
//	(options->minus && options->conversion == 'o') ? options->minus = 0 : 0;
//	(options->zero && options->conversion == 'o') ? options->zero = 0 : 0;
//	(options->zero && options->conversion == 'u') ? options->zero = 0 : 0;
	(options->plus && options->conversion == 'x') ? options->plus = 0 : 0;
	(options->plus && options->conversion == 'X') ? options->plus = 0 : 0;
	(options->space && options->conversion == 'x') ? options->space = 0 : 0;
	(options->space && options->conversion == 'X') ? options->space = 0 : 0;*/
	return (1);
}

void	ft_flag_save(char *s, t_options *options, int *i)
{
	while (s[*i] && (s[*i] == '#' || s[*i] == '0' || s[*i] == '-' || s[*i] == '+' || s[*i] == ' '))
	{
		(s[*i] == '0') ? options->zero += 1 : 0;
		(s[*i] == '-') ? options->minus += 1 : 0;
		(s[*i] == '+') ? options->plus += 1 : 0;
		(s[*i] == '#') ? options->pound += 1 : 0;
		(s[*i] == ' ') ? options->space += 1 : 0;
		*i += 1;
	}
}

int	ft_check_and_save(char *s, int *i, t_options *options)
{
	*i += 1;
	ft_flag_save(s, options, i);
	if (s[*i] && ((s[*i] > '0' && s[*i] <= '9')))
	{
		options->w += 1;
		options->width = (ft_atoi(&s[*i]));
		*i += ft_nbrlen(ft_atoi(&s[*i]));
	}
	if (s[*i] && (s[*i] == '.'))
	{
		*i += 1;
		options->p += 1;
		options->precision = (ft_atoi(&s[*i]));
		*i += ft_nbrlen(ft_atoi(&s[*i]));
	}
	if (ft_modifier_check(s, i, options) == -1)
		return (0);
	while (s[*i])
	{
		if (s[*i] && (s[*i] == 's' || s[*i] == 'S' || s[*i] == 'p' || s[*i] == 'd' || s[*i] == 'D' || s[*i] == 'i' || s[*i] == 'C' || s[*i] == 'o' || s[*i] == 'O' || s[*i] == 'u' || s[*i] == 'U' || s[*i] == 'x' || s[*i] == 'X' || s[*i] == 'c'))
		{
			options->c += 1;
			options->conversion = s[*i];
			break ;
		}
		*i += 1;
	
	}
	if (options->w <= 1 && options->p <= 1 && options->m <= 1 && options->c == 1 && ft_default_to(options))
		return (1);
	else
		return (0);
}

static	int	get_snumlen(intmax_t num)
{
	int	i;

	i = 1;
	while (num /= 10)
		i++;
	return (i);
}

/*
** The ft_itoa_smax() function takes a number, which can be as large as
** intmax_t, and converts it into a string.
*/

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
	{
		return (NULL);
	}
	str[len] = '\0';
	str[--len] = tmp % 10 + '0';
	while (tmp /= 10)
		str[--len] = tmp % 10 + '0';
	if (num < 0)
		str[0] = '-';
	return (str);
}

static	int	get_unumlen(size_t num, int base)
{
	int	i;

	i = 1;
	while (num /= base)
		i++;
	return (i);
}

char		*ft_itoabase_umax(size_t num, int base)
{
	char			*str;
	int				len;
	char			*basestr;
//	printf("%d\n", num);

	basestr = ft_strdup("0123456789abcdef");
	len = get_unumlen(num, base);
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

void	ft_apply_flags(char *s, t_options *options)
{
//	int	x;
//	s = (options->pound && options->conversion == 'o' && !options->zero) ? ft_strjoin("0", s) : s;
//	(options->width) -= ft_strlen(s);
//	(options->precision) ? options->width -= options->precision : 0;
//	(options->plus) ? options->width -= 1 : 0;
//	(options->space && s[0] != '-') ? options->width -= 1 : 0;
//	(options->plus && s[0] != '-' && options->width > 0 && options->zero) ? write(1, "+", 1) : 0;
/*	(options->minus)*/1 ? ft_putstr(s, options) : 0;
//	x = options->width;
//	while (x > 0)
//	{
//		(options->zero) ? write(1, "0", 1) : 0;
//		(!options->zero) ? write(1, " ", 1) : 0;
//		x -= 1;
//	}
//	(options->plus && s[0] != '-' && options->width && !options->minus && !options->zero) ? write(1, "+", 1) : 0;
//	(options->space && s[0] != '-') ? write(1, " ", 1) : 0;
//	(!options->minus) ? ft_putstr(s, options) : 0;
}

char	*ft_my_type(va_list *args, t_options *options, int base)
{
	char	*s;

	if (!options->modifier)
		s = ft_itoa(va_arg(*args, int));
	else if (options->modifier == "j" || options->modifier == "z")
		s = ft_itoabase_umax(va_arg(*args, intmax_t), base);
	else if (options->modifier = "ll")
		s = ft_itoabase_umax(va_arg(*args, long long), base);
	else if (options->modifier == "l")
		s = ft_itoabase_umax(va_arg(*args, long), base);
	else if (options->modifier == "hh")
		s = ft_itoabase_umax((char)va_arg(*args, int), base);
	else if (options->modifier == "h")
		s = ft_itoabase_umax((short)va_arg(*args, int), base);	
	else
		s = ft_itoabase_umax(va_arg(*args, intmax_t), base);
//	s = options->data > 0 ? ft_itoabase_umax(options->data, base, options) : ft_itoa_smax(options->data);
}

void	ft_handle_it(t_options *options, va_list *args)
{	
	if (options->conversion == 's')
		ft_apply_flags(va_arg(*args, char*), options);
	if (options->conversion == 'c')
	{
		char	s[2]; 
		s[0] = (va_arg(*args, int));
		ft_apply_flags(s, options);
	}
	if (options->conversion == 'o' || options->conversion == 'O')
		ft_apply_flags(ft_my_type(args, options, 8), options);
	if (options->conversion == 'd' || options->conversion == 'i')
		ft_apply_flags(ft_my_type(args, options, 10), options);
	if (options->conversion == 'x' || options->conversion == 'X' || options->conversion == 'p')
		ft_apply_flags(ft_my_type(args, options, 16), options);
	if (options->conversion == 'u')
		ft_putstr(ft_itoabase_umax(va_arg(*args, intmax_t), 10), options);

}
	
int	ft_printf(const char *format, ...)
{
	va_list		args;
	int		i;
	int		ret;
	t_options	options;

	i = 0;
	ret = 0;
	va_start(args, format);
	if (!format)
		return (0);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == '%')
		{
			write(1, "%", 1);
			i += 1;
		}
		else if (format[i] == '%')
		{
			ft_init_options(&options);
			if (ft_check_and_save((char*)format, &i, &options))
				ft_handle_it(&options, &args);	
		}
		else
			write(1, &format[i], 1);
		i++;
	}
	return (1);
}
/*
int main()
{
//	ft_printf("%qqqqqqq\n", "test");
//	ft_printf("Handling %%%%: %%\n");
//	ft_printf("Octal: %#o\n", 10);
//	ft_printf("String: % s\n", "Hello World!");
	ft_printf("Integer: %u\n", 4294967295 );
//	ft_printf("Lowercase Hex: % x\n", 42);
//	ft_printf("Upercase Hex: %X\n", 42);
//	printf("Ascii Charcter: %c\n", '*');
//	ft_printf("Unsigned int: %030u\n", 214783649);
//	ft_printf("Basic text: Test test 123\n");
	return (0);
}*/

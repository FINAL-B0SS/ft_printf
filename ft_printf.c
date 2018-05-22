#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <wchar.h>
#include <limits.h>
#include <locale.h>

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
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_putendl(char *s)
{
	ft_putstr(s);
	write(1, "\n", 1);
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
}		t_options;

void	ft_init_options(t_options *options)
{
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
}

int	ft_modifier_double_check(char *s, int *i, t_options *options)
{
	if (s[*i] && (s[*i] == 's' || s[*i] == 'S' || s[*i] == 'p' || s[*i] == 'd' || s[*i] == 'D' || s[*i] == 'i' || s[*i] == 'C'
				|| s[*i] == 'o' || s[*i] == 'O' || s[*i] == 'u' || s[*i] == 'U' || s[*i] == 'x' || s[*i] == 'X' || s[*i] == 'c'))
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
		return (ft_modifier_double_check(&s[*i], i + 2, options));
	}
	if (s[*i] == 'h' && s[*i] != 'h')
	{
		options->modifier = "h";
		return (ft_modifier_double_check(&s[*i], i + 1, options));
	}
	if (s[*i] == 'l' && s[*i] != 'l')
	{
		options->modifier = "l";
		return (ft_modifier_double_check(&s[*i], i + 1, options));
	}
	if (s[*i] == 'l' && s[*i] == 'l')
	{
		options->modifier = "ll";
		return (ft_modifier_double_check(&s[*i], i + 2, options));
	}
	if (s[*i] == 'j')
	{
		options->modifier = "j";
		return (ft_modifier_double_check(&s[*i], i + 1, options));
	}
	if (s[*i] == 'z')
	{
		options->modifier = "z";
		return (ft_modifier_double_check(&s[*i], i + 1, options));
	}
	return (2);
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

int	ft_default_to(t_options *options)
{
	int	ret;

	ret = 1;
	(options->space && options->plus) ? options->space = 0 : 0;
	(options->zero && options->minus) ? options->zero = 0 : 0;
	return (ret ? 1 : 0);
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
	if (s[*i] && (s[*i] == 's' || s[*i] == 'S' || s[*i] == 'p' || s[*i] == 'd' || s[*i] == 'D' || s[*i] == 'i' || s[*i] == 'C' || s[*i] == 'o' || s[*i] == 'O' || s[*i] == 'u' || s[*i] == 'U' || s[*i] == 'x' || s[*i] == 'X' || s[*i] == 'c'))
	{
		options->c += 1;
		options->conversion = s[*i];
		//	printf("f: %d\nw: %d\np: %d\nm: %d\nc: %d\n", options->f, options->w, options->p, options->m, options->c);
		//	printf("plus: %d\nminus: %d\npound: %d\nzero: %d\nspace: %d\nwidth: %d\nprecision: %d\n", options->plus, options->minus, options->pound, options->zero, options->space, options->width, options->precision);
	}
	if (options->w <= 1 && options->p <= 1 && options->m <= 1 && options->c == 1 && ft_default_to(options))
		return (1);
	else
		return (0);
}

char	*ft_otoa(unsigned long int number)
{
	char		*print;
	unsigned int	i;

	i = 0;
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
	return (ft_strrev(print));
}

char	*ft_htoa(unsigned long int number, t_options *options)
{
	char	*print;
	int	i;

	i = 0;
	print = (char*)malloc(sizeof(char) * 18);
	if (number == 0)
		print[i] = '0';
	while (number && options->conversion == 'x')
	{
		print[i++] = "0123456789abcdef"[number % 16];
		number /= 16;
	}
	while (number && options->conversion == 'X')
	{
		print[i++] = "0123456789ABCDEF"[number % 16];
		number /= 16;
	}
	return (ft_strrev(print));
}

char	*ft_uitoa(unsigned int nbr)
{
	unsigned int	tmp;
	unsigned int	count;
	char		*str;

	count = 1;
	tmp = nbr;
	while (tmp /= 10)
		count++;
	if (!(str = (char*)malloc(sizeof(char) * count)))
		return (NULL);
	while (count--)
	{
		str[count] = nbr >= 10 ? (nbr % 10) + 48 : nbr + 48;
		nbr /= 10;
	}
	str[ft_strlen(str)] = '\0';
	return (str);
}

void	ft_apply_flags(char *s, t_options *options)
{
	int	x;

	options->width ? options->width -= ft_strlen(s) : 0;
	(options->plus) ? options->width -= 1 : 0;
	(options->space && s[0] != '-') ? options->width -= 1 : 0;
	((options->plus && s[0] != '-' && options->width > 0 && options->zero) || options->minus) ? write(1, "+", 1) : 0;
	(options->minus) ? ft_putstr(s) : 0;
	x = options->width;
	while (x > 0)
	{
		(options->zero) ? write(1, "0", 1) : 0;
		(!options->zero) ? write(1, " ", 1) : 0;
		x -= 1;
	}
	(options->plus && s[0] != '-' && options->width && !options->minus) ? write(1, "+", 1) : 0;
	(options->space && s[0] != '-') ? write(1, " ", 1) : 0;
	(!options->minus) ? ft_putstr(s) : 0;
}

void	ft_handle_it(t_options *options, va_list *args)
{	
	if (options->conversion == 's')
		ft_apply_flags(va_arg(*args, char*), options);
	if (options->conversion == 'c')
		ft_putchar(va_arg(*args, int));
	if (options->conversion == 'o')
		ft_apply_flags(ft_otoa(va_arg(*args, unsigned long int)), options);
	if (options->conversion == 'd' || options->conversion == 'i')
		ft_apply_flags(ft_itoa(va_arg(*args, int)), options);
	if (options->conversion == 'x' || options->conversion == 'X')
		ft_apply_flags(ft_htoa(va_arg(*args, unsigned long int), options), options);
	if (options->conversion == 'u')
		ft_putstr(ft_uitoa(va_arg(*args, unsigned int)));
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
			else
				return (0);
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
//	printf("% +-#010d\n", 4242);
	ft_printf("Handling %%%%: %%\nOctal: %o\nString: %s\nInteger: % +d\nLowercase Hex: %x\nUpercase Hex: %X\nAscii Charcter: %c\nUnsigned int: %u\nBasic text: Test test 123\n", 10, "Hello World!", 42, 10, 10, 'A', 2147483649);
	return (0);
}*/

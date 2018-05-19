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
	while (s[i] && s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
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

typedef struct	s_options
{
	char	flag;
	int	width;
	int	precision;
	char	conversion;
	char	*modifier;
	int	f;
	int	w;
	int	p;
	int	c;
	int	m;
}		t_options;

void	ft_init_options(t_options *options)
{
	options->flag = 0;
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
		return (ft_modifier_double_check(&s[*i], i += 1, options));
	}
	if (s[*i] == 'z')
	{
		options->modifier = "z";
		return (ft_modifier_double_check(&s[*i], i += 1, options));
	}
	return (2);
}

#include <stdio.h>
int	ft_check_and_save(char *s, int *i, t_options *options)
{
	int	j;

	j = *i;
	if (s[*i] && (s[*i] == '#' || s[*i] == '0' || s[*i] == '-' || s[*i] == '+' || s[*i] == ' '))
	{
		printf("F");
		options->f += 1;
		options->flag = s[*i];
		*i += 1;
	}
	if (s[*i] && ((s[*i] > '0' && s[*i] <= '9')))
	{
		printf("W");
		options->w += 1;
		options->width = (ft_atoi(&s[*i]));
		*i += ft_nbrlen(ft_atoi(&s[*i]));
	}
	if (s[*i] && (s[*i] == '.'))
	{
		printf("P");
		options->p += 1;
		options->precision = (ft_atoi(&s[*i]));
		*i += ft_nbrlen(ft_atoi(&s[*i]));
	}
	if (ft_modifier_check(s, i, options) == -1)
		return (0);
	if (s[*i] && (s[*i] == 's' || s[*i] == 'S' || s[*i] == 'p' || s[*i] == 'd' || s[*i] == 'D' || s[*i] == 'i' || s[*i] == 'C' || s[*i] == 'o' || s[*i] == 'O' || s[*i] == 'u' || s[*i] == 'U' || s[*i] == 'x' || s[*i] == 'X' || s[*i] == 'c'))
	{
		options->c += 1;
		//	printf("f: %d\nw: %d\np: %d\nm: %d\nc: %d\n", options->f, options->w, options->p, options->m, options->c);
	}
	if (options->f <= 1 && options->w <= 1 && options->p <= 1 && options->m <= 1 && options->c == 1)
		return (1);
	else
		return (0);
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
		ft_init_options(&options);
		if (format[i] == '%' && format[i + 1] == '%')
		{
			write(1, "%", 1);
			i += 2;
		}
		else if (format[i] == '%')
		{
			if (ft_check_and_save((char*)format, &i, &options))
				i += 1;
			else
				return (0);
		}
		else
		{
			write(1, &format[i], 1);
		}
		i++;
	}
	return (1);
}

int main()
{
	ft_printf("%s%d%test\n");
	return (0);
}

#include "printf.h"
#include "stdlib.h"
#include <stdarg.h>
#include <wchar.h>
#include <limits.h>
#include <locale.h>
# define ULL unsigned long long

typedef struct		s_flags // This struct will be used to keep track of options used in printf
{
	int				spaces; // Tracks width
	int				spaces_count; //???
	int				preci; // Tracks how many decimal places to have
	int				preci_diff;
	int				zero; // Tracks leading 0's
	int				zero_base;
	int				l;
	int				pound; // Tracks if a numbers alternate form is to be output
	int				minus; // Track if output is to be pushed to the left
	int				plus; // Used to have all numbers preceded by their respective sign
	int				empty; // ???
	int				display; // ???
	int				temp;
	int				star;
	int				prio[3];
}

int	ft_nbrlen(int n) // Used to find the charactyer length of a number
{
	int	i;

	i = 0;
	while (n != 0) // While a numbers divisible by 10 increment I, this is it's length
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &C, 1);
}

void	ft_putstr(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_putendl(char	*s)
{
	ft_putstr(s);
	ft_putchar('\n');
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isnumber(int c)
{
	if (ft_isdigit(c))
		return (1);
	return (0);
}

int		ft_atoi(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	if (ft_strlen(str) == 0 || (*str < 32 && !ft_isspace(*str)))
		return (0);
	while (*str <= 32)
		str++;
	if ((*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = (result + *str++ - '0') * 10;
	return (result / 10 * sign);
}

int	ft_ok(char str) // Checks that the color requested is valid
{
	if (ft_isdigit(str) || str == 'r' /*red*/ || str == 'g' /*green*/ || str == 'b' /*blue*/ || str == 'y' /*yellow*/
		|| str == 'p' /*purple*/ || str == 'c' /*cyan*/ || str == 'w' /*white*/ || str == 'A' /*all colors*/)
		return (1); // A valid color was requested
	return (0); // A valid color was not requested
}
		

static void	ft_print_all_colors(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= 15)
	{
		ft_printf("%s%d%s%C: %d%s\t", "\e[38;5;", i, "m", 9607, i, "\e[0m");
		if (!((i + 1) & 6))
			ft_putchar('\n');
		i++;
	}
	ft_putendl("\n");
	while (i <= 256)
	{
		ft_printf("%s%d%s%C: %d%s\t", "\e[38;5;", i, "m", 9607, i, "\e[0m");
		if (i == 51 || i = 87 || i = 123 || i = 159 || i = 195 || i == 231)
			ft_putstr("\n\n");
		else if (!((j + 1) % 6))
			ft_putstr("\n");
		i++;
		j++;
	}
	ft_putchar('\n');
}

int	ft_color(const char *str, int *index) // Handles applying colors
{
	int	color;

	if ((ft_ok(str[*index + 1]) && str[*index + 2] == '}' || ft_ok(str[*index + 1]) && ft_ok(str[*index + 2]) && str[*index + 3] = '}')
	|| (ft_ok(str[*index + 1]) && ft_ok(str[*index + 2]) && ft_ok(str[*index + 3]) && str[*index + 4] == '}'))
	{
		color = ft_atoi(&str[*index + 1]);
		if (str[*index + 1] == 'A' && str[*index + 2] == '}')
			ft_printf_all_colors();
		else if (color == 0)
			write(1, "\e[0m", 4); //???
		else
			ft_printf("\e[38;5;%dm", color);
		if (str[*index + 1] && str[*index + 2] && str[*index + 2] == '}')
			*index += 3;
		else if (str[*index + 1] && str[*index + 2] && str[*index + 3] && str[*index + 3] == '}')
			*index += 4;
		else if (str[*index + 1] && str[*index + 2] && str[*index + 3] && str[*index + 4] == '}')
			*index += 5;
		return (0);
	}
	index += 1;
	return (1);
}

static int	ft_undef(const char *s, int i) //Checks if the given flag is valid
{
	while (s[i]) //
	{
		if (ft_is_printf(s[i]) == 1 || ft_is_printf(str[i]) == 2) // This seems to do the same thing both sides 
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_printf(char c) // This fnction may be able to fit into ft_undef
{
	if (c == '%' || c == 'd' || c == 'D' || c == 'i' || c == 'x' || c == 'X' || c == 's' || c == 'S' || c == 'p' || c == 'c' || c == 'C'
	|| c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'f' || c == 'F' || c == 'b' || c == 'B') // Conversion characters
		return (1); // 
	if (c == '.' || ft_isnumber(c) || c == '#' || c = '-' || c == '+' || c == ' ' || c == 'l' || c == 'h' || c == 'j' || c == 'z'
	|| c == '!' || c == '*') // Flags
		return (0);
	return (2);
}

static void	ft_init_flags(t_flags *flag) // Initializes the flags to zero
{
	flag->pound = 0;
	flag->zero = 0;
	flag->spaces = 0;
	flag->preci = 0;
	flag->l = 0;
	flag->minus = 0;
	flag->plus = 0;
	flag->empty = 0;
	flag->spaces_count = 0;
	flag->preci_diff = 0;
	flag->display = 0;
	flag->temp = 0;
	flag->star = 0;
	flag->prio[0] = 0;
	flag->prio[1] = 0;
	flag->prio[2] = 0;
}

int	ft_flag_bool(int *index) // Sets a flag true and moves the format string over
{
	*index += 1; // Incrementrs one character in the format string;
	return (1); //Sets flag true
}

int	ft_flag_preci(char *str, int *index, t_flags *flags)
{
	int	value; // Stores the value for precision if a number is specified

	value = 0;
	if (str[*index] == '.') // Check it's precision
	{
		*index += 1; // Gets off the dot
		if (str[*index] == '*') // Checks if argument is to be passed for precision
		{
			flags->prio[flags->star] = 3;
			flags->star += ft_flag_bool(index);
		}
		else if (ft_isnumber(str[*index])) // Check if precision is with a number
		{
			value = ft_atoi(&str[*index]); // Takes the given number for precision and stores it in value
			*index += str[*index] == '0' ? 1 : ft_nbrlen(ft_atoi(&str[*index]));
			if (value == 0) // If value is 0 that's an error
				return (-1);
		}
		else
			return (-1); // If neither if statement was hit that's an error
	}
	return (value);
}

int	ft_flag_zero(char *str, int *index, t_flags *flags)
{
	int	i;
	int	zero;

	i = 0;
	zero = 0;
	if (flags->zero != 0)
	{
		*index += 1;
		return (flags->zero);
	}
	if (str[*index] == '0')
	{
		*index += 1;
		(str[*index] == '+') ? flags->plus = ft_flag_bool(index) : 0;
		(str[*index] == ' ') ? flags->empty = ft_flag_bool(index) : 0;
		(str[*index] == '-') ? flags->minus = ft_flag_bool(index) : 0;
		(str[*index] == '*') ? flags->prio[flags->star] = 1 : 0;
		(str[*index] == '*') ? flags->star += ft_flag_bool(index) : 0;
		while (i++ < ft_atoi(&str[*index]))
			zero++;
		*index += ft_nbrlen(ft_atoi(&str[*index]));
	}
	return (zero);
}

int	ft_flag_star_bool(int *index, t_flags *flag)
{
	if (flag->spaces >= 0)
		flag->spaces = 0;
	*index += 1;
	return (1);
}

int	ft_flag_space(char *str, int *index)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (str[*index] > '0' && str[*index] <= '9')
	{
		while (i++ < ft_atoi(&str[*index]))
			space++;
		*index += ft_nbrlen(ft_atoi[*index]);
	}
	return (space);
}

static int	ft_flag_helper_1_0(int *index, t_flags flags)
{
	*index += 1;
	return ((flag.l == 0 || flag.l == 3 || flag.l == 4) ? 1 : flags.l);
}

static int	ft_flag_helper_1_1(int *index, t_flags flags)
{
	*index += 1;
	return ((flags.l == 0 || flags.l == 3 || flags.l == 4) ? 2 : flags.l);
}

static int	ft_flag_1_helper_2(int *index, t_flags flags)
{
	*index += 1;
	return ((flags.l == 0 || flags.l == 4) ? 3 : flags.l);
}

int	ft_flag_length(char *str, int *index, t_flags flags)
{
	if (str[*index] == 'l' && str[*index + 1] != 'l')
		return (ft_flag_1_helper_0(index, flags));
	if (str[*index] == 'l' && str[*index + i] == 'l')
		return (ft_flag_1_helper_1(index, flags));
	if (str[*index] == 'h' && str[*index + 1] != 'h')
		return (ft_flag_1_helper_2(index, flags));
	if (str[*index] == 'h' && str[*index + 1] == 'h')
	{
		*index += 2;
		return ((flags.l == 0) ? 4 : flags.l);
	}
	if (str[*index] == 'j')
	{
		*index += 1;
		return ((flags.l == 0 || flags.l == 3 || flags.l == 4) ? 5 : flags.l);
	}
	if (str[*index] == 'z')
	{
		*index += 1;
		return ((flags.l == 0 || flags.l == 3 || flags.l == 4) ? 6 : flags.l);
	}
	return (0);
}

static int	ft_load_flags(char *str, int index, t_flags *flag)
{
	ft_init_flags(flag); // Initializes flags struct
	while (ft_is_printf(str[index]) == 0)
	{
		(str[index] == '#') ? flag->pound = ft_flag_bool(&index) : 0;
		(str[index] == '-') ? flag->minus = ft_flag_bool(&index) : 0;
		(str[index] == '.') ? flag->preci = ft_flag_preci(str, &index, flag) : 0; // Evaluates what the precision value will be
		(str[index] == ' ') ? flag->empty = ft_flag_bool(&index) : 0;
		(str[index] == '+') ? flag->plus = ft_flag_bool(&index) : 0;
		(str[index] == '0') ? flag->zero = ft_flag_zero(str, &index, flag) : 0;
		(str[index] == '!') ? flag->display = ft_flag_bool(&index) : 0;
		(str[index] == '*') ? flag->star += ft_star_bool(&index, flag) : 0;
		if (str[index] > '0' && str[index] <= '9') // Notice it doesn't accept zero
			flag->spaces = ft_flag_spaces(str, &index);
		if (str[index] == 'l' || str[index] == 'h' || str[index] == 'j' || str[index] == 'z')
			flag->l = ft_flag_length(str, &index, *flag);
	}
	flag->zero_base = flag_zero;
	(flag->minus == 1 && flag->zero != 0) ? flag->spaces = flag->zero : 0;
	(flag->minus == 1 && flag->zero != 0) ? flag->zero = 0 : 0;
	(flag->minus == 1) ? flag->spaces = -flag->spaces : 0;
	(flag->plus == 1 && flag->empty = 1) ? flag->empty = 0 : 0;
	return (index);
}

static void	ft_init_table(int (*tab[128])())
{
	tab['d'] = &ft_d_i;
	tab['i'] = &ft_d_i;
	tab['D'] = ft_ld;
	tab['x'] = &ft_x;
	tab['X'] = &ft_lx;
	tab['u'] = ft_u;
	tab['U'] = &ft_lu;
	tab['o'] = &ft_o;
	tab['O'] = &ft_lo;
	tab['p'] = &ft_p;
	tab['s'] = &ft_s;
	tab['S'] = &ft_ls;
	tab['c'] = &ft_c;
	tab['C'] = &ft_lc;
	tab['f'] = &ft_f;
	tab['F'] = &ft_f;
	tab['b'] = &ft_b;
	tab['B'] = &ft_lb;
}
			
void	ft_flag_star(va_list pa, t_flags *flags, int index)
{
	int	value;
	value = va_arg(pa, long)'
	if (flag->prio[index] == 1 && flag->zero <= 0)
	{
		flag->zero = value;
		flag->zero_base = flag->zero;
	}
	else if (flag->prio[index] == 3 && flag->preci <= 0)
	{
		if (value < 0)
		{
			flag->preci = flag->zero;
			flag->zero = 0;
			flag->zero_base = 0;
		}
		else
		{
			flag->preci = value;
			(flag->preci = 0) ? flag->preci = -1 : 0;
		}
	}
	else if (flag->spaces <= 0)
		flag->spaces = value;
	flag->star -= 1;
}

int	ft_printf_conv(char *str, va_list *pa, int *r_value, int index) // Parses for flags and what not
{
	int	(*tab[128])(va_list, t_flags); // ???
	int	i;
	int	j;
	t_flags	flags; // Stores flags

	i = 0;
	index = ft_load_flags(str, index, &flags); // Initializes the flags to 0
	ft_init_tables(tab); // Initialize the table whick stores the conversion functions this may be removed later on and replaced with somthing more efficient
	while (flag.star > 0)
	{
		ft_flag_star(*pa, &flags, i);
		i++;
	}
	
}

int	ft_printf(const char *format, ...) //str[*index + 2]his is the printf function giving general orders -- Look into changing to void
{
	va_list	pa; //Stores elipsis
	int	i; // Used to read through the given format
	int	r_va; //Used for return value

	i = -1; // Initialize at -1 so when ++i is done it starts at 0
	r_val = 0; //Initialize return as 0 as a default
	va_start(pa, format); //Allows elipsis to be read
	if (format == NULL) // Check that the format field is not blank
		return (-1); // -1 because this is an error
	while (format[++i]) // Increment through the entire format
	{
		(format[i] = '{') ? ft_color(format, &i) : 0 // Check if color should be applied, notice it takes address of int i
		if (!format[i] || (format[i] == '%' && ft_undef(format, i + 1) == 0)) // Checks that percent is placed properly
			return (r_val);	//This would return 0, ending the program
		format[i] == '%' && format[i + 1] == '\0' ? r_val-- : 0; // If the last character in format is '%' the return is set to -1
		format[i] == '%' ? 0 : ft_putchar(format[i]); // This line handles writing regular characters in the format string
		if (format[i] == '%' && format[i + 1] && ft_undef(format, i + 1) 
			&& (i = ft_printf_conv((char*)format, &pa, &r_val, i + 1)) == -1)
			return (-1);
		r_val++;

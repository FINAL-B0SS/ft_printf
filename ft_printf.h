/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maljean <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 02:15:39 by maljean           #+#    #+#             */
/*   Updated: 2018/06/06 02:34:40 by maljean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

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
	int		p;
	int		c;
	int		bytes;
}				t_ops;

char	*ft_zeros(char *s, t_ops *ops);
char	*ft_strcat(char *dest, const char *src);
char	*ft_spaces(char *s, t_ops *ops);
char	*ft_chop(char *s, t_ops *ops, int i);
void	ft_apply_flags(char *s, t_ops *ops);
void	ft_handle_it(t_ops *ops, va_list args);
void	ft_init_ops(t_ops *ops);
char	*ft_mod_cast(va_list args, t_ops *ops, int base);
char	*ft_hex_cast(va_list args, t_ops *ops, int base);
void	ft_putwstr(wchar_t *ws, t_ops *ops);
wchar_t	*ft_wchrtostr(wchar_t wchar);
char	*ft_itoa(int nbr, t_ops *ops, int length, int sign);
int		get_unumlen(size_t num, int base, int i);
char	*ft_itoabase_umax(size_t num, int base, t_ops *ops);
int		get_snumlen(intmax_t num, int i);
char	*ft_itoa_smax(intmax_t num);
int		ft_atoi(char *s, int i, int nb, int sign);
char	*ft_otoa(unsigned long int number, t_ops *ops);
char	*ft_ptoa(unsigned long int number, t_ops *ops);
int		ft_printf(const char *format, ...);
int		ft_conv_check(int i, char *s, char c);
int		ft_mod_check(char *s, int *i, t_ops *ops);
void	ft_flag_save(char *s, t_ops *ops, int *i);
void	ft_prec_width_parse(char *s, int *i, t_ops *ops, va_list args);
int		ft_parse(char *s, int *i, t_ops *ops, va_list args);
void	ft_putchar(char c, t_ops *ops);
void	ft_putstr(char *s, t_ops *ops, int i);
char	*ft_strrev(char *str, int i, int length);
int		ft_strlen(char *s);
char	*ft_strcpy(char *dest, const char *src, size_t i);
int		ft_nbrlen(int n, int i);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char *s1, int i);
size_t	ft_wstrlen(const wchar_t *s, size_t len);
int		ft_strcmp(const char *s1, const char *s2);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maljean <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 02:09:27 by maljean           #+#    #+#             */
/*   Updated: 2018/06/06 03:14:29 by maljean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_nbrlen(int n, int i)
{
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char *)malloc(ft_strlen((char *)s1) +
					ft_strlen((char *)s2))))
		return (NULL);
	str = ft_strcpy(str, s1, -1);
	str = ft_strcat(str, s2);
	return (str);
}

char	*ft_strdup(char *s1, int i)
{
	int		s1_len;
	char	*str_copy;

	s1_len = ft_strlen(s1);
	str_copy = malloc(sizeof(*str_copy) * (s1_len + 1));
	if (str_copy)
	{
		while (s1[++i] != '\0')
			str_copy[i] = s1[i];
		str_copy[i] = '\0';
	}
	return (str_copy);
}

size_t	ft_wstrlen(const wchar_t *s)
{
	int	len;

	len = 0;
	while (s[len] != L'\0')
		len++;
	return (len);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
		s1++ && s2++;
	return (*(unsigned char*)s1) - *((unsigned char*)s2);
}

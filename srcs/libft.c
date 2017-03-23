/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 10:10:49 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/23 14:55:06 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <rtv1.h>

/*
static void	bzero(void *s, size_t n)
{
	char *c;

	c = s;
	if (n)
		while (n--)
			*c++ = 0;
}*/

bool				ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (true);
	return (false);
}

char	*ft_strnew(size_t size)
{
	char	*ptr;

	if ((ptr = (char *)malloc(size + 1)) != NULL)
	{
		bzero(ptr, size);
		return (ptr);
	}
	return (NULL);
}

char	*strsub(char const *s, unsigned int start, size_t len)
{
	char	*s2;

	if ((s2 = ft_strnew(len)) != NULL)
	{
		strncpy(s2, &(s[start]), len);
		return (s2);
	}
	return (NULL);
}

char	*ft_strcpy(char *dst, const char *src)
{
	char *pt_src;
	char *pt_dst;

	pt_src = (char *)src;
	pt_dst = dst;
	while (*pt_src != '\0')
	{
		*pt_dst = *pt_src;
		pt_src++;
		pt_dst++;
	}
	*pt_dst = '\0';
	return (dst);
}

static size_t	count_words(char *s, char c)
{
	size_t nb_words;

	nb_words = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != c && *s != '\0')
			nb_words++;
		while (*s != c && *s != '\0')
			s++;
	}
	return (nb_words);
}

static size_t	nb_char(char *s, char c)
{
	size_t i;

	i = 0;
	while (*s != c && *s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

static char		*create_and_fill(char **newtab, int i, char *pt_s, char c)
{
	int j;

	newtab[i] = (char *)malloc(sizeof(char) * (nb_char(pt_s, c) + 1));
	if (newtab[i] == NULL)
		return (NULL);
	newtab[i][nb_char(pt_s, c)] = '\0';
	j = 0;
	while (*pt_s != c && *pt_s != '\0')
	{
		newtab[i][j++] = *pt_s;
		pt_s++;
	}
	return (pt_s);
}

char					**ft_strsplit(const char *s, char c)
{
	char	**newtab;
	char	*pt_s;
	int		i;
	size_t	nb_words;

	if (s == NULL)
		return (NULL);
	pt_s = (char *)s;
	nb_words = count_words(pt_s, c);
	if ((newtab = (char **)malloc(sizeof(char *) * (nb_words + 1))) == NULL)
		return (NULL);
	newtab[nb_words] = NULL;
	i = 0;
	while (i < (int)nb_words)
	{
		while (*pt_s == c && *pt_s != '\0')
			pt_s++;
		if (*pt_s != c && *pt_s != '\0')
		{
			if ((pt_s = create_and_fill(newtab, i, pt_s, c)) == NULL)
				return (NULL);
		}
		i++;
	}
	return (newtab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 10:10:49 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/22 16:14:06 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

bool	ft_isdigit(int c)
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
		ft_memset(ptr, '\0', size);
		return (ptr);
	}
	return (NULL);
}

char	*strsub(char const *s, unsigned int start, size_t len)
{
	char	*s2;

	if ((s2 = ft_strnew(len)) != NULL)
	{
		ft_strncpy(s2, &(s[start]), len);
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == src || n == 0)
		return ((void *)dest);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

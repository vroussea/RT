/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 10:32:58 by pfichepo          #+#    #+#             */
/*   Updated: 2017/04/07 10:33:00 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cur;

	if (len == 0)
		return (b);
	cur = (unsigned char *)b;
	while (len--)
	{
		*cur = (unsigned char)c;
		if (len)
			cur++;
	}
	return (b);
}

char	*ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t		cur;

	cur = 0;
	while (s2[cur] != '\0' && cur < n)
	{
		s1[cur] = s2[cur];
		cur++;
	}
	while (cur < n)
	{
		s1[cur] = '\0';
		cur++;
	}
	return (s1);
}

char	*ft_strstr(const char *str, const char *to_find)
{
	int		i;
	int		j;
	int		c;

	i = 0;
	c = 0;
	if (to_find[0] == '\0')
		return (char*)(str);
	while (str[i] != '\0')
	{
		j = i;
		c = 0;
		while (str[j] == to_find[c])
		{
			j++;
			c++;
			if (to_find[c] == '\0')
				return (char*)(&str[i]);
		}
		i++;
	}
	return (NULL);
}

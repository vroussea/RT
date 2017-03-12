/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 10:57:53 by pfichepo          #+#    #+#             */
/*   Updated: 2017/02/01 10:57:54 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	updatepixel(t_envgui *env, int x, int y, Uint32 color)
{
	double	v;
	int		nb;

	nb = y;
	env->aaupdated = env->aa;
	putpixel(env->raysurface[env->aa], x, y, color);
	v = math_remapsimple(nb, env->raysurface[env->aa]->h, 1);
	env->isloading = (nb != env->w * env->h);
	env->loadingvalue = v;
	env->drag = 0;
}



void *ft_memset(void *b, int c, size_t len)
{
	size_t bytes;

	bytes = 0;
	while (bytes < len)
	{
		((char *)b)[bytes] = (unsigned char)c;
		bytes++;
	}
	return (b);
}

void	ft_memdel(void **ap)
{
	if (ap && *ap)
	{
		free(*ap);
		*ap = NULL;
	}
}


void	*ft_memalloc(size_t size)
{
	void	*alloc;

	alloc = malloc(size);
	if (alloc)
		alloc = ft_memset(alloc, 0, size);
	return (alloc);
}

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}



void	ft_bzero(void *s, size_t n)
{
	if (n > 0)
		ft_memset(s, 0, n);
}

void	ft_putstr(char const *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

void	ft_strdel(char **as)
{
	if (as && *as)
		ft_memdel((void **)as);
}

char *ft_strnew(size_t size)
{
	char *str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}
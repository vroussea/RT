/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 13:08:54 by pfichepo          #+#    #+#             */
/*   Updated: 2017/02/09 13:08:55 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static Uint32			avercolor(Uint32 *tbl)
{
	Uint32				r;
	Uint32				g;
	Uint32				b;
	unsigned int		i;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (i < (AANUM))
	{
		r += (tbl[i] >> 16 & 255);
		g += (tbl[i] >> 8 & 255);
		b += (tbl[i] >> 0 & 255);
		i++;
	}
	return (rgba((r / i), (g / i), (b / i)));
}

static Uint32			getaapixel(t_envgui *env, int posx, int posy)
{
	Uint32	*tbl;
	int		x;
	int		i;
	int		y;

	x = 0;
	i = 0;
	tbl = (Uint32 *)malloc(sizeof(Uint32) * AANUM);
	while (AALEVEL > x)
	{
		y = 0;
		while (AALEVEL > y)
		{
			tbl[i] = getpixel(env->raysurface[1], posx + x, posy + y);
			i++;
			y++;
		}
		x++;
	}
	return (avercolor(tbl));
}

void					calcaa(t_envgui *env)
{
	int x;
	int y;

	if (env->aa == 0)
		return ;
	x = 0;
	while (x < env->raysurface[0]->w)
	{
		y = 0;
		while (y < env->raysurface[0]->h)
		{
			putpixel(env->raysurface[0], x, y, \
				getaapixel(env, x * AALEVEL, y * AALEVEL));
			y++;
		}
		x++;
	}
}

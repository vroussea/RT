/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 11:43:31 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/23 11:43:32 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.H>
#include <rt.h>

Uint32		convert(Uint32 color)
{
	Uint8 r;
	Uint8 g;
	Uint8 b;

	b = (color >> 16 & 0xff);
	g = (color >> 8 & 0xff);
	r = (color >> 0 & 0xff);
	return ((b << 24) + (g << 16) + (r << 8));
}

void		convertsurface(SDL_Surface *sur)
{
	int		x;
	int		y;
	Uint32	tempcol;

	x = 0;
	while (x < sur->w)
	{
		y = 0;
		while (y < sur->h)
		{
			tempcol = convert(getpixel(sur, x, y));
			putpixel(sur, x, y, tempcol);
			y++;
		}
		x++;
	}
}

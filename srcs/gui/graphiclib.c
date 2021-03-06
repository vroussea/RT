/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphiclib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 10:51:03 by pfichepo          #+#    #+#             */
/*   Updated: 2017/01/25 11:57:20 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

Uint32		rgba(Uint32 r, Uint32 g, Uint32 b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void		putpixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
	Uint8			*pixel;
	unsigned int	sz;

	if (!surface)
		return ;
	sz = sizeof(Uint32);
	pixel = (Uint8*)surface->pixels;
	pixel += ((Uint32)y * (Uint32)surface->pitch) + ((Uint32)x * sz);
	*((Uint32*)pixel) = color;
}

Uint32		getpixel(SDL_Surface *surface, int x, int y)
{
	Uint8			*pixel;
	unsigned int	sz;

	sz = sizeof(Uint32);
	pixel = (Uint8*)surface->pixels;
	pixel += ((Uint32)y * (Uint32)surface->pitch) + ((Uint32)x * sz);
	return (*((Uint32*)pixel));
}

SDL_Rect	*newrect(int x, int y, int w, int h)
{
	SDL_Rect *ret;

	ret = (SDL_Rect*)malloc(sizeof(SDL_Rect));
	ret->x = x;
	ret->y = y;
	ret->w = w;
	ret->h = h;
	return (ret);
}

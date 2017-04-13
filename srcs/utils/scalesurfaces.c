/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalesurfaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 11:32:11 by pfichepo          #+#    #+#             */
/*   Updated: 2017/04/04 11:32:17 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		whilemdr(t_imgstruct *st, SDL_Surface *s, SDL_Surface *ret)
{
	st->x = 0;
	while (st->x < s->w)
	{
		st->o_y = 0;
		while (st->o_y < st->fy)
		{
			st->o_x = 0;
			while (st->o_x < st->fx)
			{
				putpixel(ret, (int)(st->fx * st->x) + st->o_x,
					(int)(st->fy * st->y) + st->o_y, getpixel(s, st->x, st->y));
				++st->o_x;
			}
			++st->o_y;
		}
		st->x++;
	}
	st->y++;
}

SDL_Surface	*scalesurface(SDL_Surface *s, Uint16 w, Uint16 h)
{
	t_imgstruct	*st;
	SDL_Surface	*ret;

	if (!s || !w || !h)
		return (0);
	st = (t_imgstruct*)malloc(sizeof(t_imgstruct));
	ret = SDL_CreateRGBSurface(s->flags, w, h, s->format->BitsPerPixel,
		s->format->Rmask, s->format->Gmask, s->format->Bmask, s->format->Amask);
	st->fx = ((double)(w) / (double)(s->w));
	st->fy = ((double)(h) / (double)(s->h));
	st->y = 0;
	while (st->y < s->h)
	{
		whilemdr(st, s, ret);
	}
	free(st);
	return (ret);
}

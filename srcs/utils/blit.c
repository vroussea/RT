/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 13:09:45 by pfichepo          #+#    #+#             */
/*   Updated: 2017/04/13 13:09:46 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void MDR_BlitSurface(SDL_Surface *src, SDL_Surface *dst, int x, int y)
{
	int x1;
	int y1;
	x1 = 0;

	while (x1 < src->w)
	{
		y1 = 0;
		while (y1 < src->h)
		{
			putpixel(dst, x1 + x, y1 + y, getpixel(src, x1, y1));
			y1++;
		}
		x1++;
	}
	return ;
}

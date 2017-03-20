/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flares.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 08:34:50 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/20 08:34:51 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <rt.h>
#include <SDL_image.h>



void drawflare(SDL_Surface *target, int x, int y, double distance)
{
	int x1;
	int y1;
	double dist;

	distance = 1 + (distance - 0) * (0 - 1) / (40 - 0);
	printf("%f\n",distance*10 );
	x1 = 0;
	y1 = 0;
	while (x1 < target->w)
	{
		y1 = 0;
		while (y1 < target->h)
		{
			dist = sqrt(pow((x1 - x), 2) + pow((y1 - y), 2));
			if (dist < distance*10)
			{
				putpixel(target, x1, y1,(Uint32)(( 255 << 24) + (255 << 16) + (255 << 8) + (255)));
			}
			y1++;
		}
		x1++;
	}
}


static double realdist(double dist)
{
	return math_remapsimple(dist, 701.783442,7);
}


bool		spotvisible(int *xy, double *spot, t_obj *blist)
{
	double	nearest_point;
	double	mem;
	t_obj	*nearest_obj;
	t_obj	*list;

	list = blist;
	while (list != NULL)
	{
		if ((mem = list->intersect(xy, list)) < nearest_point)
		{
			nearest_point = mem;
			nearest_obj = list;
		}
		list = list->next;
	}
	if (nearest_point > realdist(spot[2]) \
		&& spot[0] == xy[0] && spot[1] == xy[1])
	{
		return (true);
	}
	return (false);
}

void processflares(SDL_Surface *target, t_obj *blist, SDL_Surface *flare)
{
	double **list;
	Uint32 i;
	int xy[2];

	xy[0] = 0;
	while (xy[0] < target->w)
	{
		xy[1] = 0;
		while (xy[1] < target->h)
		{
			i = 0;
			list = blist->recap_spots;
			while (i < blist->nb_spots_on_screen)
			{
				if (spotvisible(xy, list[i], blist))
				{
					SDL_Rect rect;
					rect.w = flare->w;
					rect.h = flare->h;
					rect.x = xy[0] - (rect.w)/2;
					rect.y = xy[1] - (rect.h)/2;
					SDL_BlitSurface(flare, NULL, target, &rect);

				}

				i++;
			}
			xy[1]++;
		}
		xy[0]++;
	}
}














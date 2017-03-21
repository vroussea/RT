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
#include <SDL2_rotozoom.h>



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

void processflares(SDL_Surface *target, t_obj *blist, SDL_Surface *flare, int aa)
{
	double **list;
	Uint32 i;
	int xy[2];
	double dist;
	SDL_Surface *tmp;

	i = 0;
	list = blist->recap_spots;
	while (i < blist->nb_spots_on_screen)
	{
		if (spotvisible(xy, list[i], blist))
		{
			printf("%i %i \n", xy[0], xy[1]);
			dist = 1 + (realdist(list[i][2]) - 0) * (0 - 1) / (40 - 0);
			tmp = rotozoomSurface(flare, rand() % 360, (dist / 6.5)*aa, 1);
			SDL_Rect rect;
			rect.w = tmp->w;
			rect.h = tmp->h;
			rect.x = xy[0] - (tmp->w) / 2;
			rect.y = xy[1] - (tmp->h) / 2;
			SDL_BlitSurface(tmp, NULL, target, &rect);
			SDL_FreeSurface(tmp);
		}
		i++;
	}
}














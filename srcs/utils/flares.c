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

#include <rt.h>
#include <SDL_image.h>
#include <SDL2_rotozoom.h>

double			realdist(double dist)
{
	return (math_remapsimple(dist, 701.783442, 7));
}

bool			spotvisible(int *xy, double *spot, t_obj *blist)
{
	double	nearest_point;
	double	mem;
	t_obj	*nearest_obj;
	t_obj	*list;

	list = blist;
	nearest_obj = NULL;
	nearest_point = 2147483647;
	while (list != NULL)
	{
		if ((mem = list->intersect(xy, list)) < nearest_point)
		{
			nearest_point = mem;
			nearest_obj = list;
		}
		list = list->next;
	}
	if (nearest_point > realdist(spot[2]))
		return (true);
	return (false);
}

static double	getgoodsize(double *tab, int aa)
{
	double	centerdist;
	int		x;
	int		y;
	double	fact;

	x = 1920;
	y = 1038;
	if (aa > 1)
	{
		x *= AALEVEL;
		y *= AALEVEL;
	}
	centerdist = sqrt(pow((x / 2 - tab[0]), 2) + pow((y / 2 - tab[1]), 2));
	fact = 1 + (realdist(tab[2]) - 0) * (0 - 1) / (40 - 0);
	if (centerdist < (200 * aa))
		fact *= (5 + (centerdist - 0) * (0 - 5) / (200 * aa));
	return (fact);
}

void			processflares(SDL_Surface *t, t_obj *b, SDL_Surface *f, int a)
{
	Uint32		i;
	int			xy[2];
	double		dist;
	SDL_Surface	*tmp;
	SDL_Rect	rect;

	i = 0;
	while (i < b->nb_spots_on_screen)
	{
		xy[0] = b->recap_spots[i][0];
		xy[1] = b->recap_spots[i][1];
		if (spotvisible(xy, b->recap_spots[i], b))
		{
			dist = getgoodsize(b->recap_spots[i], a);
			tmp = rotozoomSurface(f, (i * 49) % 360, (dist / 6.5) * a, 1);
			rect.w = tmp->w;
			rect.h = tmp->h;
			rect.x = xy[0] - (tmp->w) / 2;
			rect.y = xy[1] - (tmp->h) / 2;
			SDL_BlitSurface(tmp, NULL, t, &rect);
			SDL_FreeSurface(tmp);
		}
		i++;
	}
}

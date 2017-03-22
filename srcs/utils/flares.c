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

double	realdist(double dist)
{
	return (math_remapsimple(dist, 701.783442, 7));
}

bool	spotvisible(int *xy, double *spot, t_obj *blist)
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

void	processflares(SDL_Surface *t, t_obj *b, SDL_Surface *f, int aa)
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
			dist = 1 + (realdist(b->recap_spots[i][2]) - 0) * \
			(0 - 1) / (40 - 0);
			tmp = rotozoomSurface(f, rand() % 360, (dist / 6.5) * aa, 1);
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

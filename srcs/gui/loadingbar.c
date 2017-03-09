/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadingbar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 10:22:28 by pfichepo          #+#    #+#             */
/*   Updated: 2017/01/26 10:22:31 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		drawrect(SDL_Surface *surface, t_pos *pos, Uint32 color)
{
	int	x;
	int	x2;
	int	y;
	int	y2;

	x = 0;
	while (x < pos->w)
	{
		x2 = pos->x + x;
		y = 0;
		while (y < pos->h)
		{
			y2 = pos->y + y;
			putpixel(surface, x2, y2, color);
			y++;
		}
		x++;
	}
}

void		drawloadingbar(t_envgui *env)
{
	int		x;
	int		y;
	int		w;
	int		h;
	t_pos	*pos;

	pos = env->gui->percentbox;
	w = env->w / 3;
	h = env->h / 15;
	x = env->w / 2 - w / 2;
	y = env->h / 2 - h / 2;
	pos->w = (int)((double)w * env->loadingvalue);
	pos->h = h;
	pos->x = x;
	pos->y = y;
	drawrect(env->surface, pos, 0xffffff);
}

void		drawloadingbardiscrete(t_envgui *env)
{
	int		x;
	int		y;
	int		w;
	int		h;
	t_pos	*pos;

	pos = env->gui->percentbox;
	w = env->w;
	h = 10;
	x = 0;
	y = env->h - 11;
	pos->w = (int)((double)w * env->loadingvalue);
	pos->h = h;
	pos->x = x;
	pos->y = y;
	drawrect(env->surface, pos, 0xffffff);
}

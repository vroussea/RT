/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 12:27:45 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/16 16:13:26 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

double			math_remapsimple(double value, double to1, double to2)
{
	return (value * (to2 / to1));
}

/*
**le y42 est uniquement là pour la norme
*/

bool				isinbutton(t_button *button, int x, int y)
{
	int			x2;
	int			y2;
	double		distance;
	SDL_Rect	*bpos;
	int			y42;

	bpos = button->pos;
	x2 = bpos->x;
	y2 = bpos->y;
	y42 = (y2 + bpos->h);
	if (button->type == BUTTON_BOX)
		return (((x > x2) && (x < (x2 + bpos->w))) && ((y > y2) && (y < y42)));
	x2 = bpos->x + bpos->w / 2;
	y2 = bpos->y + bpos->h / 2;
	if (button->type == BUTTON_SPHERE)
	{
		distance = sqrt(pow((x2 - x), 2) + pow((y2 - y), 2));
		if (distance <= bpos->w / 2)
			return (true);
	}
	return (false);
}

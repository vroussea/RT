/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 10:23:25 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/09 10:23:27 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void	startdrag(t_envgui *e, int press, int y)
{
	if (e->drag && press == 0)
		e->drag = 0;
	if (y < 33)
	{
		e->drag = press;
		SDL_GetGlobalMouseState(&e->dragx, &e->dragy);
	}
}

void		mouse_press(SDL_Event *ev, int press, t_envgui *e)
{
	t_button	*button;
	int			x;
	int			y;

	x = ev->button.x;
	y = ev->button.y;
	if (press == 0 && e->lastpressed && (e->currentbutton != e->lastpressed))
		e->lastpressed->pressed = 0;
	if (e->currentbutton)
	{
		button = e->currentbutton;
		if (press)
		{
			button->pressed = 1;
			e->lastpressed = e->currentbutton;
		}
		else
		{
			if (e->currentbutton == e->lastpressed)
				button->pressfunc(e, button);
			button->pressed = 0;
		}
	}
	else 
		startdrag(e, press, y);
}

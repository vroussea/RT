/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flarebuttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:30:48 by pfichepo          #+#    #+#             */
/*   Updated: 2017/04/11 11:30:50 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void		ralo(t_envgui *env, t_button *self)
{
	SDL_Surface *tmp;

	tmp = self->press2;
	self->press2 = self->press;
	self->press = tmp;
	tmp = self->defaults2;
	self->defaults2 = self->defaults;
	self->defaults = tmp;
	env->flares = !env->flares;
	env->redraw = 1;
}

void			buttonflares(t_envgui *env)
{
	t_button *button;
	SDL_Rect *p4;

	p4 = newrect(env->w - 320, 0, 32, 32);
	button = newbutton("res/flr1def.bmp", "res/flr1press.bmp", p4);
	button->togglable = 1;
	button->defaults2 = SDL_LoadBMP("res/flr0def.bmp");
	button->press2 = SDL_LoadBMP("res/flr0press.bmp");
	if (!button->press2 || !button->defaults2)
		ft_error("Cannot Load button texture", NULL);
	button->pressed = 0;
	button->type = BUTTON_SPHERE;
	button->pressfunc = (void*)ralo;
	stackbutton(env, button);
}

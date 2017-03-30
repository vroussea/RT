/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 11:38:44 by pfichepo          #+#    #+#             */
/*   Updated: 2017/02/01 11:38:45 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_button	*newbutton(char *def, char *press, SDL_Rect *pos)
{
	t_button *ret;

	ret = (t_button*)malloc(sizeof(t_button));
	if (!(ret->defaults = SDL_LoadBMP(def)))
		ft_error("Cannot Load button texture", NULL);
	if (!(ret->press = SDL_LoadBMP(press)))
		ft_error("Cannot Load button texture", NULL);
	ret->pos = pos;
	ret->next = NULL;
	return (ret);
}

void		closewinfunc(t_envgui *env, t_button *self)
{
	self = (t_button*)self;
	env->threaddone = 1;
	SDL_WaitThread(env->thread, NULL);
	SDL_DestroyRenderer(env->renderer);
	SDL_DestroyWindow(env->win);
	SDL_Quit();
	exit(0);
}

void		reducewinfunc(t_envgui *env, t_button *self)
{
	self = (t_button*)self;
	SDL_MinimizeWindow(env->win);
}

void		togglefpsfunc(t_envgui *env, t_button *self)
{
	self = (t_button*)self;
	env->drawfps = !env->drawfps;
}

void		stackbutton(t_envgui *env, t_button *button)
{
	t_button *pos;

	pos = env->buttons;
	while (pos->next)
		pos = pos->next;
	pos->next = button;
}

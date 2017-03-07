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
	ret->defaults = SDL_LoadBMP(def);
	ret->press = SDL_LoadBMP(press);
	ret->pos = pos;
	ret->next = NULL;
	return (ret);
}

int			closewinfunc(t_envgui *env, t_button *self)
{
	self = (t_button*)self;
	SDL_DestroyRenderer(env->renderer);
	SDL_DestroyWindow(env->win);
	SDL_Quit();
	exit(0);
}

int			reducewinfunc(t_envgui *env, t_button *self)
{
	self = (t_button*)self;
	SDL_MinimizeWindow(env->win);
	return (1);
}

int			togglefpsfunc(t_envgui *env, t_button *self)
{
	self = (t_button*)self;
	env->drawfps = !env->drawfps;
	return (1);
}

void		stackbutton(t_envgui *env, t_button *button)
{
	t_button *pos;

	pos = env->buttons;
	while (pos->next)
		pos = pos->next;
	pos->next = button;
}

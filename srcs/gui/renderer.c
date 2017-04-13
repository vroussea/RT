/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:09:54 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/29 17:26:39 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void		drawfps(t_envgui *env)
{
	sprintf(env->gui->fpstext, "%i", env->currentfps);
	env->gui->fpsfont = TTF_RenderText_Solid(env->gui->sans,\
		env->gui->fpstext, env->gui->white);
	MDR_BlitSurface(env->gui->fpsfont, env->surface, env->gui->fpsrect->x, env->gui->fpsrect->y );
	SDL_FreeSurface(env->gui->fpsfont);
}

/*
** Routine est là pour check les fps et le déplacement de la window
*/

void			routine(t_envgui *env, Uint32 deltacock, Uint32 startcock)
{
	int				posx;
	int				posy;
	int				winx;
	int				winy;
	double			current;

	current = (double)deltacock / (double)1000;
	if (current < ((double)1 / (double)env->freq))
		SDL_Delay((Uint32)((((double)1 / (double)env->freq) - current) * 1000));
	if (deltacock != 0)
		env->currentfps = (Uint32)(((double)1 / (SDL_GetTicks() - \
	startcock) * 1000));
	if (env->drag)
	{
		SDL_GetGlobalMouseState(&posx, &posy);
		SDL_GetWindowPosition(env->win, &winx, &winy);
		SDL_SetWindowPosition(env->win, winx + \
			(posx - env->dragx), winy + (posy - env->dragy));
		env->dragx = posx;
		env->dragy = posy;
	}
}

/*
** On push les surfaces, calc buttons, etc
*/

static t_button	*retnext(t_button *button, t_envgui *env)
{
	if (button->pressed)
		MDR_BlitSurface(button->press, env->surface, button->pos->x, button->pos->y);
	else
		MDR_BlitSurface(button->defaults, env->surface, button->pos->x, button->pos->y);
	return (button->next);
}

void			mainrender(t_envgui *env, char **argv)
{
	if (env->redraw)
	{
		draw_the_image(argv, env);
		env->redraw = 0;
	}
	if (env->aaupdated && env->aa == 1)
	{
		calcaa(env);
		env->aaupdated = 0;
	}
}

int				threaddraw(void *e)
{
	t_envgui	*a;
	t_button	*button;
	Uint32		startclock;
	double		current;

	a = (t_envgui*)e;
	while (1 && !a->threaddone)
	{
		startclock = SDL_GetTicks();
		SDL_RenderClear(a->renderer);
		MDR_BlitSurface(a->gui->bar, a->surface, 0, 0);
		button = a->buttons;
		while (button)
			button = retnext(button, a);
		SDL_LowerBlit(a->raysurface[0], a->rayrectin, a->surface, a->rayrect);
		if (a->isloading)
			drawloadingbardiscrete(a);
		if (a->drawfps && a->gui->sans)
			drawfps(a);
		SDL_UpdateWindowSurface(a->win);
		current = (double)(SDL_GetTicks() - startclock) / (double)1000;
		if (current < ((double)1 / (double)a->freq))
			SDL_Delay((Uint32)((1 / (double)a->freq) - current) * 1000);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:09:54 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/03 17:20:18 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <rtv1.h>

static void		drawfps(t_envgui *env)
{
	sprintf(env->gui->fpstext, "%i", env->currentFPS);
	env->gui->fpsfont = TTF_RenderText_Solid(env->gui->sans,\
		env->gui->fpstext, env->gui->white);
	SDL_BlitSurface(env->gui->fpsfont, NULL, env->surface, env->gui->fpsrect);
	SDL_FreeSurface(env->gui->fpsfont);
}

/*
** Routine est là pour check les fps et le déplacement de la window
*/

void			routine(t_envgui *env, Uint32 deltaclock, Uint32 startclock)
{
	int				posx;
	int				posy;
	int				winx;
	int				winy;
	double			current;

	current = (double)deltaclock / (double)1000;
	if (current < ((double)1 / (double)env->freq))
		SDL_Delay((Uint32)((((double)1 / (double)env->freq) - current) * 1000));
	if (deltaclock != 0)
		env->currentFPS = (Uint32)(((double)1 / (SDL_GetTicks() - \
	startclock) * 1000));
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
		SDL_BlitSurface(button->press, NULL, env->surface, button->pos);
	else
		SDL_BlitSurface(button->defaults, NULL, env->surface, button->pos);
	return (button->next);
}

void			mainrender(t_envgui *env, t_obj *lst, char **argv)
{
	if (env->redraw)
	{
		draw_the_image(argv, lst, env);
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
		SDL_BlitSurface(a->gui->bar, NULL, a->surface, NULL);
		button = a->buttons;
		while (button)
			button = retnext(button, a);
		SDL_LowerBlit(a->raysurface[0], a->rayrectin, a->surface, a->rayrect);
		if (a->isloading)
			drawloadingbardiscrete(a);
		if (a->drawfps)
			drawfps(a);
		SDL_UpdateWindowSurface(a->win);
		current = (double)(SDL_GetTicks() - startclock) / (double)1000;
		if (current < ((double)1 / (double)a->freq))
			SDL_Delay((Uint32)((1 / (double)a->freq) - current) * 1000);
	}
	return (1);
}

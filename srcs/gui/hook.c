/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:33:54 by pfichepo          #+#    #+#             */
/*   Updated: 2017/01/25 11:59:21 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static int		key_press(SDL_Event *e, t_envgui *env)
{
	if (e->key.keysym.sym == SDLK_ESCAPE)
	{
		SDL_DestroyRenderer(env->renderer);
		SDL_DestroyWindow(env->win);
		SDL_Quit();
		exit(0);
	}
	return (0);
}

static void		window_resized(SDL_Event *e, t_envgui *env)
{
	env->w = e->window.data1;
	env->h = e->window.data2;
	free(env->rayrect);
	SDL_FreeSurface(env->surface);
	SDL_FreeSurface(env->raysurface);
	SDL_DestroyRenderer(env->renderer);
	env->surface = SDL_GetWindowSurface(env->win);
	env->renderer = SDL_CreateSoftwareRenderer(env->surface);
	SDL_SetRenderDrawColor(env->renderer, 0, 0, 0, 255);
	env->raysurface = SDL_CreateRGBSurfaceWithFormat(0, \
	env->w, env->h - 10 - env->gui->bar->h, 32, SDL_PIXELFORMAT_RGB888);
	env->rayrect = newrect(0, env->gui->bar->h, env->w, \
	env->h - 10 - env->gui->bar->h);
}

static void		calccursor(t_envgui *env, int x, int y)
{
	t_button	*found;
	t_button	*button;

	found = NULL;
	button = env->buttons;
	while (button)
	{
		if (isinbutton(button, x, y))
		{
			found = button;
			break ;
		}
		button = button->next;
	}
	env->currentbutton = found;
	if (found)
		SDL_SetCursor(env->hand);
	else
		SDL_SetCursor(env->arrow);
}

static void		mouse_move(SDL_Event *e, t_envgui *env)
{
	int	posx;
	int	posy;
	int	winx;
	int	winy;

	if (env->drag)
	{
		SDL_GetGlobalMouseState(&posx, &posy);
		SDL_GetWindowPosition(env->win, &winx, &winy);
		SDL_SetWindowPosition(env->win, winx +\
		(posx - env->dragx), winy + (posy - env->dragy));
		env->dragx = posx;
		env->dragy = posy;
	}
	else
		calccursor(env, e->motion.x, e->motion.y);
}

static void		mouse_press(SDL_Event *e, int press, t_envgui *env)
{
	t_button	*button;
	int			x;
	int			y;

	x = e->button.x;
	y = e->button.y;
	if (press == 0 && env->lastpressed && (env->currentbutton != env->lastpressed))
		env->lastpressed->pressed = 0;
	if (env->currentbutton)
	{
		button = env->currentbutton;
		if (press)
		{
			button->pressed = 1;
			env->lastpressed = env->currentbutton;
		}
		else
		{
			if (env->currentbutton == env->lastpressed)
				button->pressfunc(env, button);
			button->pressed = 0;
		}
	}
	else if (y < 33)
	{
		env->drag = press;
		SDL_GetGlobalMouseState(&env->dragx, &env->dragy);
	}
}

int				main_event(SDL_Event *e, t_envgui *env)
{
	int events;

	events = 0;
	if (e->type == SDL_QUIT)
	{
		SDL_DestroyRenderer(env->renderer);
		SDL_DestroyWindow(env->win);
		SDL_Quit();
		exit(0);
	}
	if (e->type == SDL_KEYDOWN)
		events += key_press(e, env);
	if (e->type == SDL_MOUSEMOTION)
		mouse_move(e, env);
	if (e->type == SDL_WINDOWEVENT)
		if (e->window.event == SDL_WINDOWEVENT_RESIZED)
			window_resized(e, env);
	if (e->type == SDL_MOUSEBUTTONDOWN)
		mouse_press(e, 1, env);
	if (e->type == SDL_MOUSEBUTTONUP)
		mouse_press(e, 0, env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:33:54 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/16 16:15:27 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static int		key_press(SDL_Event *e, t_envgui *env)
{
	if (e->key.keysym.sym == SDLK_ESCAPE)
	{
		env->threaddone = 1;
		SDL_WaitThread(env->thread, NULL);
		SDL_DestroyRenderer(env->renderer);
		SDL_DestroyWindow(env->win);
		SDL_Quit();
		exit(0);
	}
	if (e->key.keysym.sym == SDLK_F5)
		env->redraw = true;
	return (0);
}

static void		calccursor(t_envgui *env, int x, int y)
{
	t_button	*found;
	t_button	*button;
	SDL_Cursor	*target;

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
		target = env->hand;
	else
		target = env->arrow;
	if (SDL_GetCursor() == target)
		return ;
	SDL_SetCursor(target);
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

void			main_event(SDL_Event *e, t_envgui *env)
{
	if (env->isloading)
		return ;
	if (e->type == SDL_QUIT)
	{
		SDL_Quit();
		exit(0);
	}
	if (e->type == SDL_KEYDOWN)
		key_press(e, env);
	if (e->type == SDL_MOUSEMOTION)
		mouse_move(e, env);
	if (e->type == SDL_MOUSEBUTTONDOWN)
		mouse_press(e, 1, env);
	if (e->type == SDL_MOUSEBUTTONUP)
		mouse_press(e, 0, env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 14:21:25 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/10 10:12:40 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <rt.h>

void		ft_error(char *str, char **tab)
{
	if (tab != NULL)
		write(2, "Error: file not well formated\n", 30);
	else
		perror(str);
	exit(-1);
}

#if WIN32
# pragma comment (lib, "sdl2.lib")
# pragma comment (lib, "sdl2main.lib")
#endif

t_envgui	*initenv(void)
{
	t_envgui *env;

	env = (t_envgui*)malloc(sizeof(t_envgui));
	env->w = WIN_W;
	env->h = WIN_H;
	env->freq = 60;
	env->win = SDL_CreateWindow("rt", SDL_WINDOWPOS_CENTERED, \
	SDL_WINDOWPOS_CENTERED, env->w, env->h, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL );
	env->surface = SDL_GetWindowSurface(env->win);
	env->renderer = SDL_CreateSoftwareRenderer(env->surface);
	SDL_SetRenderDrawColor(env->renderer, 0, 0, 0, 255);
	initgui(env);
	env->arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	env->hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	env->wait = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT);
	env->isloading = 0;
	env->loadingvalue = 0;
	env->drag = 0;
	env->drawfps = 1;
	env->aa = 0;
	env->aaupdated = 1;
	env->redraw = 1;
	return (env);
}

int			main(int argc, char **argv)
{
	t_envgui		*env;
	Uint32			startclock;
	SDL_Event		e;

	if (argc != 2)
		ft_error("Usage: ./rt <filename>\n", NULL);
	checkread(argv[1]);
	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER);
	TTF_Init();
	env = initenv();
	initbuttons(env);
	startclock = SDL_GetTicks();
	env->currentFPS = 0;
	env->thread = SDL_CreateThread(threaddraw, "RenderingThread", (void*)env);
	while (1)
	{
		startclock = SDL_GetTicks();
		while (SDL_PollEvent(&e))
			main_event(&e, env);
		mainrender(env, argv);
		routine(env, SDL_GetTicks() - startclock, startclock);
	}
	return (0);
}

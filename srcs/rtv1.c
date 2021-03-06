/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 14:21:25 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/16 16:18:34 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <SDL_image.h>
#if WIN32
# pragma comment (lib, "sdl2.lib")
# pragma comment (lib, "sdl2main.lib")
# pragma comment (lib, "SDL2_ttf.lib")
# pragma comment (lib, "SDL2_image.lib")
#endif

void		ft_error(char *str, char **tab)
{
	if (tab != NULL)
		write(2, "Error: file not well formated\n", 30);
	else
		perror(str);
	exit(-1);
}

t_envgui	*initenv(void)
{
	t_envgui *env;

	env = (t_envgui*)malloc(sizeof(t_envgui));
	env->w = WIN_W;
	env->h = WIN_H;
	env->freq = 60;
	env->win = SDL_CreateWindow("rt", SDL_WINDOWPOS_CENTERED, \
	SDL_WINDOWPOS_CENTERED, env->w, env->h, SDL_WINDOW_BORDERLESS);
	env->surface = SDL_GetWindowSurface(env->win);
	env->renderer = SDL_CreateSoftwareRenderer(env->surface);
	SDL_SetRenderDrawColor(env->renderer, 0, 0, 0, 255);
	initgui(env);
	env->arrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	env->hand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	env->wait = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_WAIT);
	env->isloading = 0;
	env->loadingvalue = 0;
	env->drag = false;
	env->drawfps = 1;
	env->aa = 0;
	env->aaupdated = 1;
	env->redraw = 1;
	initbuttons(env);
	env->currentfps = 0;
	return (env);
}

int			main(int argc, char **argv)
{
	t_envgui		*env;
	Uint32			startclock;
	SDL_Event		e;

	if (argc != 2)
	{
		ft_putstr("Usage: ./rt <filename>\n");
		exit(-1);
	}
	checkread(argv[1]);
	SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	env = initenv();
	startclock = SDL_GetTicks();
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

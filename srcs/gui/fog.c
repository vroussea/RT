/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 10:00:57 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/13 10:00:59 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <SDL_image.h>

Uint32			rgbafog(double dist)
{
	Uint8	a;
	int		max;

	max = MAXFOGDIST;
	if (dist > max)
		dist = max;
	if (dist < MINFOGDIST)
		a = 0;
	else
		a = (Uint8)math_remapsimple(dist - MINFOGDIST, max, 255);
	return (Uint32)((a << 24) + (50 << 16) + (50 << 8) + (50));
}

static void		ralo(t_envgui *env, t_button *self)
{
	SDL_Surface *tmp;

	tmp = self->press2;
	self->press2 = self->press;
	self->press = tmp;
	tmp = self->defaults2;
	self->defaults2 = self->defaults;
	self->defaults = tmp;
	env->fog = !env->fog;
	env->redraw = 1;
}

void			initfog(t_envgui *env)
{
	t_button *button;
	SDL_Rect *p4;

	env->fraysurface = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 2);
	env->zraysurface = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 2);
	env->fraysurface[0] = SDL_CreateRGBSurfaceWithFormat(0, env->w, env->h \
		- 10 - env->gui->bar->h, 32, SDL_PIXELFORMAT_RGBA32);
	env->fraysurface[1] = SDL_CreateRGBSurfaceWithFormat(0, \
		env->raysurface[0]->w \
	* AALEVEL, env->raysurface[0]->h * AALEVEL, 32, SDL_PIXELFORMAT_RGBA32);
	env->zraysurface[0] = SDL_CreateRGBSurfaceWithFormat(0, env->w, env->h \
		- 10 - env->gui->bar->h, 32, SDL_PIXELFORMAT_RGBA32);
	env->zraysurface[1] = SDL_CreateRGBSurfaceWithFormat(0, \
		env->raysurface[0]->w \
	* AALEVEL, env->raysurface[0]->h * AALEVEL, 32, SDL_PIXELFORMAT_RGBA32);
	env->fog = 0;
	p4 = newrect(env->w - 275, 0, 32, 32);
	env->flare = IMG_Load("res/lens.png");
	button = newbutton("res/fogdef0.bmp", "res/fogdef1.bmp", p4);
	button->togglable = 1;
	button->defaults2 = SDL_LoadBMP("res/fogpress0.bmp");
	button->press2 = SDL_LoadBMP("res/fogpress1.bmp");
	button->pressed = 0;
	button->type = BUTTON_SPHERE;
	button->pressfunc = ralo;
	stackbutton(env, button);
}

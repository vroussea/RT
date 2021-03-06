/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initgui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 11:33:03 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/16 16:13:44 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <SDL_image.h>

static void		rala(t_envgui *env, t_button *self)
{
	SDL_Surface *tmp;

	tmp = self->press2;
	self->press2 = self->press;
	self->press = tmp;
	tmp = self->defaults2;
	self->defaults2 = self->defaults;
	self->defaults = tmp;
	env->aa = !env->aa;
	env->redraw = 1;
	return ;
}

static void		screen(t_envgui *env, t_button *self)
{
	SDL_CreateThread(threadsavepic, "WriteImageThread", \
		(void*)env->raysurface[0]);
	self = (t_button*)self;
}

static void		initbuttons2(t_envgui *env)
{
	t_button *button;
	SDL_Rect *p4;
	SDL_Rect *p5;

	p4 = newrect(env->w - 185, 0, 32, 32);
	p5 = newrect(env->w - 230, 0, 32, 32);
	button = newbutton("res/aadef0.bmp", "res/aapress0.bmp", p4);
	button->togglable = 1;
	if (!(button->defaults2 = SDL_LoadBMP("res/aadef1.bmp")))
		perror("Cannot Load button texture");
	if (!(button->press2 = SDL_LoadBMP("res/aapress1.bmp")))
		perror("Cannot Load button texture");
	button->pressed = 0;
	button->type = BUTTON_SPHERE;
	button->pressfunc = (void*)rala;
	stackbutton(env, button);
	button = newbutton("res/cameradeff.bmp", "res/camerapress.bmp", p5);
	button->pressfunc = (void*)screen;
	button->pressed = 0;
	button->type = BUTTON_SPHERE;
	stackbutton(env, button);
	if (!(env->flare = IMG_Load("res/lens.png")))
		ft_error("Cannot Load lens texture", NULL);
	initfog(env);
}

void			initbuttons(t_envgui *env)
{
	t_button *button;
	SDL_Rect *p1;
	SDL_Rect *p2;
	SDL_Rect *p3;

	p1 = newrect(env->w - 50, 0, 32, 32);
	p2 = newrect(env->w - 95, 0, 32, 32);
	p3 = newrect(env->w - 140, 0, 32, 32);
	button = newbutton("res/errordef.bmp", "res/errorpress.bmp", p1);
	button->pressfunc = (void*)closewinfunc;
	button->pressed = 0;
	button->type = BUTTON_SPHERE;
	env->buttons = button;
	button = newbutton("res/reducedef.bmp", "res/reducepress.bmp", p2);
	button->pressfunc = (void*)reducewinfunc;
	button->pressed = 0;
	button->type = BUTTON_SPHERE;
	stackbutton(env, button);
	button = newbutton("res/fpsdef.bmp", "res/fpspress.bmp", p3);
	button->pressfunc = (void*)togglefpsfunc;
	button->pressed = 0;
	button->type = BUTTON_SPHERE;
	stackbutton(env, button);
	initbuttons2(env);
	env->threaddone = 0;
}

void			initgui(t_envgui *env)
{
	env->gui = (t_gui *)malloc(sizeof(t_gui));
	env->gui->fpsfont = NULL;
	env->gui->fpstext = (char *)malloc(sizeof(char) * 100);
	env->gui->bar = SDL_CreateRGBSurfaceWithFormat(0, env->w, 32 \
		+ 1 - 1, 32, SDL_PIXELFORMAT_RGB888);
	SDL_FillRect(env->gui->bar, NULL, 0xff454545);
	env->raysurface = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 2);
	env->raysurface[0] = SDL_CreateRGBSurfaceWithFormat(0, env->w, env->h \
		- 10 - env->gui->bar->h, 32, SDL_PIXELFORMAT_RGB888);
	env->raysurface[1] = SDL_CreateRGBSurfaceWithFormat(0, \
		env->raysurface[0]->w \
	* AALEVEL, env->raysurface[0]->h * AALEVEL, 32, SDL_PIXELFORMAT_RGB888);
	env->rayrect = newrect(0, env->gui->bar->h, env->w, env->raysurface[0]->h);
	env->rayrectin = newrect(0, 0, env->w, env->raysurface[0]->h);
	if (!(env->gui->sans = TTF_OpenFont("res/Sans.ttf", 24)))
		perror("Cannot load FPS font");
	env->gui->white.r = 255;
	env->gui->white.g = 255;
	env->gui->white.b = 255;
	env->gui->white.a = 255;
	env->gui->fpsrect = newrect(50, 50, 24, 24);
	env->gui->percentbox = (t_pos*)malloc(sizeof(t_pos));
	env->currentbutton = NULL;
	env->lastpressed = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <pfichepo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 09:56:34 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/03 17:32:13 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# define WIN_W 1920
# define WIN_H 1080
# define WIN_HCAM (WIN_H - 42)
# include <SDL.h>
# include <SDL_ttf.h>
# include <math.h>
# if WIN32
#	 include <stdint.h>
# else
	 #include <unistd.h>
# endif
# include <time.h>
# include <stdbool.h>
# include <rtv1.h>
# define BUTTON_BOX 0
# define BUTTON_SPHERE 1
# define AALEVEL 2
# define AANUM AALEVEL*AALEVEL

typedef struct		s_envgui	t_envgui;
typedef struct		s_obj		t_obj;

typedef struct		s_pos
{
	int				x;
	int				y;
	int				w;
	int				h;
}					t_pos;

typedef struct		s_color
{
	Uint8			r;
	Uint8			g;
	Uint8			b;
}					t_color;

typedef struct		s_button
{
	SDL_Surface 	*press;
	SDL_Surface 	*press2;
	SDL_Surface		*defaults;
	SDL_Surface		*defaults2;
	SDL_Rect		*pos;
	bool			togglable;
	bool			pressed;
	int 			type;
	void			(*pressfunc)(t_envgui *, struct s_button *);
	struct s_button	*next;
}					t_button;

typedef struct 		s_gui
{
	t_button		*quit;
	SDL_Surface 	*bar;
	SDL_Surface		*fpsfont;
	TTF_Font 		*sans;
	SDL_Color		white;
	SDL_Rect		*fpsrect;
	char			*fpstext;
	t_pos 			*percentbox;
}					t_gui;

typedef struct		s_envgui
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Surface		*surface;
	SDL_Surface		**raysurface;
	SDL_Rect		*rayrectin;
	SDL_Rect		*rayrect;
	t_button		*buttons;
	t_button		*currentbutton;
	t_button		*lastpressed;
	int				w;
	int				h;
	int				drag;
	int				dragx;
	int				dragy;
	double			time;
	int				freq;
	t_gui			*gui;
	Uint32			currentFPS;
	bool			isloading;
	bool			drawfps;
	double			loadingvalue;
	SDL_Rect 		*surbox;
	SDL_Cursor		*arrow;
	SDL_Cursor		*hand;
	SDL_Cursor		*wait;
	bool			aa;
	bool			aaupdated;
	bool			redraw;
	SDL_Thread		*thread;
	bool			threaddone;
	SDL_Surface		**zraysurface;
	SDL_Surface		**fraysurface;
	bool			fog;
	SDL_Surface 	*flare;
}					t_envgui;

Uint32				rgba(Uint32 r, Uint32 g, Uint32 b);
void				putpixel(SDL_Surface * surface, int x, int y, Uint32 color);
Uint32				getpixel(SDL_Surface * surface, int x, int y);
int					main_event(SDL_Event *e, t_envgui *env);
void				main_loop(t_envgui *env);
void				mainrender(t_envgui *env, char **argv);
SDL_Rect			*newrect(int x, int y, int w, int h);
void				drawrect(SDL_Surface *surface, t_pos *pos, Uint32 color);
void				drawloadingbar(t_envgui *env);
void				drawloadingbardiscrete(t_envgui *env);
double				math_remapsimple(double value, double to1, double to2);
char				*ft_itoa(int n);
void				initgui(t_envgui *env);
void 				initbuttons(t_envgui *env);
bool				isinbutton(t_button *button, int x, int y);
void				routine(t_envgui *env, Uint32 deltaclock, Uint32 startclock);
void				stackbutton(t_envgui *env, t_button *button);
t_button 			*newbutton(char *def, char* press, SDL_Rect *pos);
void				closewinfunc(t_envgui *env, t_button *self);
void				reducewinfunc(t_envgui *env, t_button *self);
void				togglefpsfunc(t_envgui *env, t_button *self);
t_envgui			*initenv(void);
void 				calcaa(t_envgui *env);
void 				updatepixel(t_envgui *env, int x, int y, Uint32 color);
void				checkread(char *s);
int					threaddraw(void *e);
void				mouse_press(SDL_Event *e, int press, t_envgui *env);
Uint32				rgbafog(double	 dist);
void 				initfog(t_envgui *env);
int 				getmult(int aa);
int					threadsavepic(void *adr);
#endif

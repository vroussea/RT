/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 14:32:56 by eduwer            #+#    #+#             */
/*   Updated: 2017/04/12 19:48:54 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# include <stdbool.h>
# include <math.h>
# include <fcntl.h>
# if WIN32
#  include <stdint.h>
# else
#  include <unistd.h>
# endif
# include <libft.h>
# define TYPE_PLANE 1
# define TYPE_SPHERE 0
# define TYPE_CONE 3
# define TYPE_CYLINDER 2
# define MINFOGDIST 2
# define MAXFOGDIST 6
# define FOGO (MAXFOGDIST + MINFOGDIST)
# define PROC_TEXT_CUBE 0
# define PROC_TEXT_CIRCLE_X 1
# define PROC_TEXT_CIRCLE_Y 2
# define PROC_TEXT_CIRCLE_Z 3
# define PROC_TEXT_STRAIGHT_STRIPES 4
# define PROC_TEXT_DIAGONAL_STRIPES 5
# define G_LUM 0.1
# define PI 3.1415926535897932384626433832795
# define WIN_W 1920
# define WIN_H 1080
# include <SDL.h>
# include <SDL_ttf.h>
# include <time.h>
# include <stdbool.h>
# define BUTTON_BOX 0
# define BUTTON_SPHERE 1
# define AALEVEL 2
# define AANUM (AALEVEL * AALEVEL)

/*
** order of numbers for recap_spots in t_obj :
** recap_spots[n][0] & [1] : position of the spot on the screen
** recap_spots[n][2] : distance from the cam to the spot
** from recap_spots[n][3] to [5] : position of the spot in the space
*/

typedef struct		s_pos
{
	uint16_t	x;
	uint16_t	y;
	uint16_t	w;
	uint16_t	h;
}					t_pos;

typedef struct		s_imgstruct
{
	uint16_t	y;
	uint16_t	x;
	uint16_t	o_y;
	uint16_t	o_x;
	double		fx;
	double		fy;
}					t_imgstruct;

typedef struct		s_button
{
	SDL_Surface		*press;
	SDL_Surface		*press2;
	SDL_Surface		*defaults;
	SDL_Surface		*defaults2;
	SDL_Rect		*pos;
	bool			togglable;
	bool			pressed;
	bool			type;
	void			(*pressfunc)(void *, struct s_button *);
	struct s_button	*next;
}					t_button;

typedef struct		s_gui
{
	t_button	*quit;
	SDL_Surface *bar;
	SDL_Surface	*fpsfont;
	TTF_Font	*sans;
	SDL_Color	white;
	SDL_Rect	*fpsrect;
	char		*fpstext;
	t_pos		*percentbox;
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
	uint16_t		w;
	uint16_t		h;
	bool			drag;
	int				dragx;
	int				dragy;
	Uint8			freq;
	t_gui			*gui;
	Uint32			currentfps;
	bool			isloading;
	bool			drawfps;
	double			loadingvalue;
	SDL_Rect		*surbox;
	SDL_Cursor		*arrow;
	SDL_Cursor		*hand;
	SDL_Cursor		*wait;
	bool			aa;
	bool			aaupdated;
	bool			redraw;
	SDL_Thread		*thread;
	bool			threaddone;
	SDL_Surface		**zraysurface;
	bool			fog;
	SDL_Surface		*flare;
	bool			flares;
}					t_envgui;

typedef struct		s_obj
{
	char			type;
	double			pos[3];
	double			size;
	double			high;
	double			angle;
	double			rad;
	double			rotation[3];
	double			norm_vec[3];
	int				res[2];
	double			pos_cam[3];
	double			pos_pixel_base[3];
	double			vec_right[3];
	double			vec_down[3];
	double			**spot;
	Uint8			nb_spot;
	Uint8			nb_spots_on_screen;
	double			**recap_spots;
	int				color_rgb[3];
	int				final_color[3];
	int				color;
	double			intersec_point[3];
	double			distance;
	double			base_pos_cam[3];
	double			base_pos_pixel_base[3];
	double			base_vec_down[3];
	double			base_vec_right[3];
	double			base_vec_ray[3];
	double			base_intersec_point[3];
	double			n_normalz[3];
	double			base_norm_vector[3];
	double			(*intersect)(int*, struct s_obj*);
	void			(*vector)(double*, double*, struct s_obj*, int);
	bool			(*shadow)(struct s_obj *, double *, int);
	Uint8			proc_text_type;
	bool			is_proc_texture;
	bool			is_waves;
	Uint8			nb_ref;
	double			reflection_id;
	double			refraction_id;
	double			original_refraction;
	double			new_refraction;
	int				color1[3];
	int				color2[3];
	double			decal_xyz[3];
	Uint32			(*texturing)(struct s_obj *obj);
	SDL_Surface		*texture;
	double			text_size;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_cam
{
	double			pos_cam[3];
	double			rotation[3];
	double			vec_cam[3];
	double			pos_pixel_base[3];
	double			vec_right[3];
	double			vec_down[3];
	Uint32			nb_spot;
	double			**spot;
	int				res[2];
}					t_cam;

typedef struct		s_threaddata
{
	Uint8			threadid;
	t_obj			*data;
	SDL_Surface		*image;
	SDL_Surface		*fogmap;
	bool			aa;
	double			*loading;
}					t_threaddata;

typedef struct		s_parserdata
{
	t_threaddata	*thread1;
	t_threaddata	*thread2;
	t_threaddata	*thread3;
	t_threaddata	*thread4;
}					t_parserdata;

Uint32				rgba(Uint32 r, Uint32 g, Uint32 b);
void				putpixel(SDL_Surface *surface, int x, int y, Uint32 color);
Uint32				getpixel(SDL_Surface *surface, int x, int y);
void				main_event(SDL_Event *e, t_envgui *env);
void				main_loop(t_envgui *env);
void				mainrender(t_envgui *env, char **argv);
SDL_Rect			*newrect(int x, int y, int w, int h);
void				drawrect(SDL_Surface *surface, t_pos *pos, Uint32 color);
void				drawloadingbar(t_envgui *env);
void				drawloadingbardiscrete(t_envgui *env);
double				math_remapsimple(double value, double to1, double to2);
char				*ft_itoa(int n);
void				initgui(t_envgui *env);
void				initbuttons(t_envgui *env);
bool				isinbutton(t_button *button, int x, int y);
void				routine(t_envgui *env, Uint32 deltacock, Uint32 startcock);
void				stackbutton(t_envgui *env, t_button *button);
t_button			*newbutton(char *def, char *press, SDL_Rect *pos);
void				closewinfunc(t_envgui *env, t_button *self);
void				reducewinfunc(t_envgui *env, t_button *self);
void				togglefpsfunc(t_envgui *env, t_button *self);
t_envgui			*initenv(void);
void				calcaa(t_envgui *env);
void				updatepixel(t_envgui *env, int x, int y, Uint32 color);
void				checkread(char *s);
int					threaddraw(void *e);
void				mouse_press(SDL_Event *e, int press, t_envgui *env);
Uint32				rgbafog(double dist);
void				initfog(t_envgui *env);
uint16_t			getmult(int aa);
int					threadsavepic(void *adr);
char				*ft_strnew(size_t size);
char				*strsub(char const *s, unsigned int start, size_t len);
void				get_infos(char *filename, t_obj **objs, int is_aa);
bool				init_tab_3(double tab[3], int color[3], char *line);
bool				init_3_values(double pos[3], char *line, char *pattern);
bool				init_colors(int color[3], char *line);
bool				init_one_value(double *value, char *line, char *pattern);
void				init_default_cam_values(t_cam *cam, int is_aa);
void				init_default_sphere_values(t_cam *cam, t_obj *objs);
void				init_default_plane_values(t_cam *cam, t_obj *objs);
void				init_default_cylinder_values(t_cam *cam, t_obj *objs);
void				init_default_cone_values(t_cam *cam, t_obj *objs);
bool				get_cam_infos(int fd, t_cam *cam, int is_aa);
bool				init_spots(int fd, t_cam *cam);
bool				get_objs_infos(int fd, t_obj *objs, t_cam *cam);
bool				init_sphere(int fd, t_obj *objs, t_cam *cam);
bool				init_plane(int fd, t_obj *objs, t_cam *cam);
bool				init_cylinder(int fd, t_obj *objs, t_cam *cam);
bool				init_cone(int fd, t_obj *objs, t_cam *cam);
t_obj				*make_new_obj(t_obj *objs, int type);
bool				check(char *line, t_obj *new_obj, int fd);
void				finish_init_obj(t_obj *obj, t_cam *cam);
void				init_down_right(double vec_down[3], double vec_right[3], \
						double rotation[3], int res[2]);
void				init_functs_obj(t_obj *obj);
void				init_sphere_functs(t_obj *obj);
void				init_plane_functs(t_obj *obj);
void				init_cone_functs(t_obj *obj);
void				init_cylinder_functs(t_obj *obj);
void				convert_to_hex(int tab[3]);
void				verif_plane_norm_vec(t_obj *plane);
bool				init_one_spot(t_cam *cam);
bool				init_procedural_textures(t_obj *obj, int fd);
bool				init_procedural_type(t_obj *obj, char *line);
void				init_obj_values(t_obj *obj);
bool				check_procedural_texture(t_obj *obj, char *line);
int					*get_proc_color(t_obj *obj);
void				free_spots(t_cam *cam);
void				init_recap_spots(t_obj *obj, t_cam *cam);
void				calc_reflection_refraction(t_obj *l, t_obj *o, int c[3]);
bool				init_ref(double *ref, char *line, char *balise);
t_obj				*copy_the_list(t_obj *list, t_obj *obj, double ray[3]);
void				free_copied_list(t_obj *list);
void				get_reflected_color(t_obj *list, t_obj *obj, int color[3]);
void				get_refracted_color(t_obj *list, t_obj *obj, int color[3]);
double				calc_one_spot_luminosity(t_obj *obj, int nb);
double				calc_one_spot_spec(t_obj *obj, int nb);
void				draw_the_image(char **argv, struct s_envgui *env);
int					calc_image(int x, int y, t_obj *b, SDL_Surface *f);
int					get_color_obj(t_obj *begin_list, t_obj *nearest_obj, \
						int xy[2]);
void				get_color_tab(int color[3], t_obj *list);
double				get_intersec(int xy[2], t_obj *list);
double				intersec_cone(int xy[2], t_obj *list);
void				abc_cone(double abc[3], double vec_ray[3], \
						double base_pos[3], double rad);
double				intersec_cylinder(int xy[2], t_obj *list);
void				abc_cylinder(double abc[3], double vec_ray[3], \
						double base_pos[3], double size);
double				intersec_plane(int xy[2], t_obj *list);
double				intersec_sphere(int xy[2], t_obj *list);
void				get_new_pos_cam(double cam[3], double base_pos[3], \
									double obj[3]);
void				abc_sphere(double abc[3], double vec[3], \
						double pos[3], double size);
void				del_all_list(t_obj *list);
void				calc_luminosity(int color_tab[3], t_obj *nearest_obj, \
						int nb_spot);
void				get_vectors(double norm_vector[3], double vec_light[3], \
						t_obj *obj, int nb_spot);
double				radians(double degree);
void				rotation_x(double vec[3], double degree);
void				rotation_y(double vec[3], double degree);
void				rotation_z(double vec[3], double degree);
void				make_rotation(double vec[3], double rotation[3], int rev);
void				rotation(double vec[3], double axe[3], double ang);
void				normalize_vec(double vec[3]);
double				calc_2nd_degree_equation(double abc[3]);
void				calc_intersec_point(t_obj *obj, double vec_ray[3]);
double				dot_product(double vec1[3], double vec2[3]);
void				reflection(double vec1[3], double norm[3], double ref[3]);
void				refraction(double v[3], double n[3], double r[3], t_obj *o);
void				ft_error(char *str, char **tab);
bool				shadows(t_obj *lst, int xy[2], \
						t_obj *obj, int nb);
int					calc_shadow_obj(t_obj *list, double point[3], int nb);
bool				shadow_sphere(t_obj *sphere, double point[3], int nb);
bool				shadow_plane(t_obj *plane, double point[3], int nb);
bool				shadow_cylinder(t_obj *cylinder, double point[3], int nb);
bool				shadow_cone(t_obj *cone, double point[3], int nb);
void				get_new_pos(double point[3], double pos_obj[3], \
						double rotation[3]);
void				get_vector_sphere(double norm_vec[3], double vec_light[3], \
						t_obj *obj, int nb);
void				get_vector_plane(double norm_vec[3], double vec_light[3], \
						t_obj *obj, int nb);
void				get_vector_cylinder(double norm_vec[3], \
						double vec_light[3], t_obj *obj, int nb);
void				get_vector_cone(double norm_vec[3], double vec_light[3], \
						t_obj *obj, int nb);
void				cross_product(double norm_vector[3], double vec1[3], \
						double vec2[3]);
double				clamp(double min, double max, double val);
void				vect_prod(double u[3], double v[3], double orth[3]);
void				initthreads(t_parserdata *data);
bool				flarecheck(double **list, int max, int x, int y);
void				proflr(SDL_Surface *t, t_obj *b, SDL_Surface *f, int a);
bool				init_surface(SDL_Surface **texture, char *line);
void				texture(t_obj *obj, int color_tab[3]);
Uint32				texture_sphere(t_obj *obj);
Uint32				texture_cylinder(t_obj *obj);
Uint32				texture_plane(t_obj *obj);
Uint32				convert(Uint32 color);
void				convertsurface(SDL_Surface *sur);
void				ft_putstr(char *str);
SDL_Surface			*scalesurface(SDL_Surface *s, Uint16 w, Uint16 h);
void				buttonflares(t_envgui *env);
#endif

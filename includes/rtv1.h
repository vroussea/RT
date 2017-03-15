/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 14:32:56 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/14 16:45:09 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H
# include <math.h>
# include <fcntl.h>
# include <rt.h>
#if WIN32
# include <stdint.h>
#else
# include <unistd.h>
#endif
# include <libft.h>
# define TYPE_PLANE 1
# define TYPE_SPHERE 0
# define TYPE_CONE 3
# define TYPE_CYLINDER 2
# define MINFOGDIST 2
# define MAXFOGDIST 6
# define FOGO MAXFOGDIST+MINFOGDIST
# define PROC_TEXT_CUBE 0
# define PROC_TEXT_CIRCLE_X 1
# define PROC_TEXT_CIRCLE_Y 2
# define PROC_TEXT_CIRCLE_Z 3
# define PROC_TEXT_STRAIGHT_STRIPES 4
# define PROC_TEXT_DIAGONAL_STRIPES 5
typedef struct		s_envgui	t_envgui;
typedef struct		s_obj 		t_obj;

/*
** list of type for s_obj :
** 0: sphere
** 1: plane
** 2:cylinder
** 3: cone
*/

typedef struct		s_proc_text
{
	int		type;
	int		color1[3];
	int		color2[3];
	double	size_xyz[3];
	double	decal_xyz[3];
}					t_proc_text;

typedef struct		s_obj
{
	int				type;
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
	Uint32			nb_spot;
	int				color_rgb[3];
	int				final_color[3];
	int				color;
	double			intersec_point[3];
	double			distance;
	double			base_pos_cam[3];
	double			base_pos_pixel_base[3];
	double			base_vec_down[3];
	double			base_vec_right[3];
	double			(*intersect)(int*, struct s_obj*);
	void			(*vector)(double*, double*, struct s_obj*, int);
	int				(*shadow)(struct s_obj *, double *, int);
	t_proc_text		*proc_texture;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_cam
{
	double		pos_cam[3];
	double		rotation[3];
	double		vec_cam[3];
	double		pos_pixel_base[3];
	double		vec_right[3];
	double		vec_down[3];
	Uint32		nb_spot;
	double		**spot;
	int			res[2];
}					t_cam;

typedef struct		s_threaddata
{
	Uint8			threadid;
	t_obj			*data;
	SDL_Surface		*image;
	SDL_Surface		*fogmap;
	bool 			aa;
	double 			*loading;
}					t_threaddata;

typedef struct 		s_parserdata
{
	t_threaddata *thread1;
	t_threaddata *thread2;
	t_threaddata *thread3;
	t_threaddata *thread4;
}					t_parserdata;





void	get_infos(char *filename, t_obj **objs, int is_aa);
int		init_scene(int fd, t_obj *objs, int is_aa);
int		init_tab_3(double tab[3], int color[3], char *line);
int		init_3_values(double pos[3], char *line, char *pattern);
int		init_colors(int color[3], char *line);
int		init_res(char *line, t_cam *cam, int is_aa);
int		init_one_value(double *value, char *line, char *pattern);
void	init_default_cam_values(t_cam *cam, int is_aa);
void	init_default_sphere_values(t_cam *cam, t_obj *objs);
void	init_default_plane_values(t_cam *cam, t_obj *objs);
void	init_default_cylinder_values(t_cam *cam, t_obj *objs);
void	init_default_cone_values(t_cam *cam, t_obj *objs);
int		get_cam_infos(int fd, t_cam *cam, int is_aa);
int		init_spots(int fd, t_cam *cam);
int		get_objs_infos(int fd, t_obj *objs, t_cam *cam);
int		init_sphere(int fd, t_obj *objs, t_cam *cam);
int		init_plane(int fd, t_obj *objs, t_cam *cam);
int		init_cylinder(int fd, t_obj *objs, t_cam *cam);
int		init_cone(int fd, t_obj *objs, t_cam *cam);
t_obj	*make_new_obj(t_obj *objs, int type);
int		check(char *line, t_obj *new_obj, int fd);
void		finish_init_obj(t_obj *obj, t_cam *cam);
void	init_down_right(double vec_down[3], double vec_right[3], \
			double rotation[3], int res[2]);
void	init_functs_obj(t_obj *obj);
void	convert_to_hex(int tab[3]);
void	verif_plane_norm_vec(t_obj *plane);
int		init_one_spot(t_cam *cam);
int		init_procedural_textures(t_obj *obj, int fd);
int		init_procedural_type(t_obj *obj, char *line);
int		check_procedural_texture(t_obj *obj, char *line);
int		*get_proc_color(t_obj *obj);

double				calc_one_spot_luminosity(t_obj *obj, int nb);
double				calc_one_spot_spec(t_obj *obj, int nb);

void				draw_the_image(char **argv, t_envgui *env);
int					calc_image(int x, int y, t_obj *begin_list, SDL_Surface *fogmap);
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
void				make_rotation(double vec[3], double rotation[3]);

void				normalize_vec(double vec[3]);
double				calc_2nd_degree_equation(double abc[3]);
void				calc_intersec_point(double pos[3], double distance, \
						double vec_ray[3], double origin[3]);
double				dot_product(double vec1[3], double vec2[3]);
void				reflexion(double vec1[3], double norm[3], double ref[3]);

void				ft_error(char *str, char **tab);

int					shadows(t_obj *lst, int xy[2], \
						t_obj *obj, int nb);
int					calc_shadow_obj(t_obj *list, double point[3], int nb);

int					shadow_sphere(t_obj *sphere, double point[3], int nb);
int					shadow_plane(t_obj *plane, double point[3], int nb);
int					shadow_cylinder(t_obj *cylinder, double point[3], int nb);
int					shadow_cone(t_obj *cone, double point[3], int nb);
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
void initthreads(t_parserdata *data);

#endif

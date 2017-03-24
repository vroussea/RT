/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_v1.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:36:29 by vroussea          #+#    #+#             */
/*   Updated: 2017/02/12 14:50:55 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_V1_H
# define RT_V1_H

# include "../libft/includes/libft.h"
# include "../libvect3d/includes/libvect3d.h"

# define SIZE_X 1000
# define SIZE_Y 1000
# define GRID_DIST 1.0
# define GRID_HEIGHT 0.25
# define GRID_WIDTH 0.25

# define SCENE_VER 1.08
# define CAM scene.pov
# define SPOT scene.spots
# define QUAD scene.quads
# define PI 3.14159265358979323846

# define SPHERE 0
# define PLANE 1
# define CYLINDER 2
# define CONE 3

# define DX dir.x
# define DY dir.y
# define DZ dir.z
# define PX pos.x
# define PY pos.y
# define PZ pos.z

# define UP scene.up
# define RIGHT scene.right
# define LEFTUP scene.leftupgrid

# pragma pack(1)

typedef	struct		s_obj
{
	int			type;
	t_vect3d	pos;
	t_vect3d	dir;
	double		size;
	int			col;
}					t_obj;

typedef struct		s_scene
{
	t_obj		pov;
	int			nb_quad;
	int			nb_spot;
	t_obj		*quads;
	t_obj		*spots;
	t_vect3d	up;
	t_vect3d	right;
	t_vect3d	leftupgrid;
}					t_scene;

typedef	struct		s_env
{
	void	*mlx;
	void	*win;
	void	*img;
}					t_env;

typedef double		(*t_functs)(t_obj, t_obj, t_scene);
typedef t_vect3d	(*t_norm_functs)(t_vect3d, t_obj);

int					add_node(void *node, t_env *env);
t_scene				get_struct(char *file);
void				caller(t_env *env, char *str, t_scene scene);
int					quit_funct(t_env *env);
int					key_funct(int keycode, t_env *env);
int					*opencl(t_scene scene);
void				*error_msg(char *str);
double				collide_sphere(t_obj ray, t_obj quad, t_scene scene);
double				collide_plan(t_obj ray, t_obj quad, t_scene scene);
double				collide_cylinder(t_obj ray, t_obj quad, t_scene scene);
double				collide_cone(t_obj ray, t_obj quad, t_scene scene);
void				pixel_browser(t_scene scene, char *meml);
void				pixel(int x, int y, int col, char *meml);
t_scene				grid_left_up_corner(t_scene scene);
int					slct_light(t_obj ray, double dist,
		t_scene scene, t_obj quad);
int					col_grad(int col, int strength);
t_vect3d			plane_normal(t_vect3d pos, t_obj plane);
t_vect3d			sphere_normal(t_vect3d pos, t_obj plane);
t_vect3d			cone_normal(t_vect3d pos, t_obj plane);
t_vect3d			cylinder_normal(t_vect3d pos, t_obj plane);

#endif

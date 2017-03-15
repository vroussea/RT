#define NULL 0

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
	unsigned int	nb_spot;
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
	struct s_obj	*next;
}					t_obj;

double				intersec_cone(int xy[2], t_obj *list);
double				intersec_cylinde(int xy[2], t_obj *list);
double				intersec_plane(int xy[2], t_obj *list);
double				intersec_sphere(int xy[2], t_obj *list);
int					get_color_obj(t_obj *begin_list, t_obj *nearest_obj, int xy[2]);

__kernel void raytracer(int x_max, __global t_obj *begin_list, __global int *col)
{
	double	nearest_point;
	double	mem;
	__global t_obj	*nearest_obj;
	__global t_obj	*list;
	int		id;
	int		xy[2];

	id = get_global_id(0);
	xy[1] = id / x_max;
	xy[0] = id % x_max;
	list = begin_list;
	nearest_obj = NULL;
	nearest_point = 2147483647;
	while (list != NULL)
	{
	//	if ((mem = list->intersect(xy, list)) < nearest_point)
	//	{
	//		nearest_point = mem;
	//		nearest_obj = list;
	//	}
		list = list->next;
	}
	if (nearest_obj == NULL)
		col[id] = 0x000000;
//	else
//		col[id] = get_color_obj(begin_list, nearest_point, xy);
}

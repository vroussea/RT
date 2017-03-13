/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:15:59 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/13 12:24:19 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <rt.h>

void	draw_the_image(char **argv, t_obj *list, t_envgui *env)
{
//	int		xy[2];
	int		xy2[2];
	int		*col;

	xy2[0] = env->raysurface[env->aa]->w;
	xy2[1] = env->raysurface[env->aa]->h;
	get_infos(argv[1], &list, env->aa);
	col = opencl("./srcs/kernels/raytracer.cl", list, xy2);
	/*xy[1] = 0;
	while (xy[1] < xy2[1])
	{
		xy[0] = 0;
		while (xy[0] < xy2[0])
		{
			updatepixel(env, xy[0], xy[1], (Uint32)calc_image(xy, list));
			xy[0]++;
		}
		xy[1]++;
	}*/
	free((void **)&col);
}

/*int		calc_image(int xy[2], t_obj *begin_list)
{
	double	nearest_point;
	double	mem;
	t_obj	*nearest_obj;
	t_obj	*list;

	list = begin_list;
	nearest_obj = NULL;
	nearest_point = 2147483647;
	while (list != NULL)
	{
		if ((mem = list->intersect(xy, list)) < nearest_point)
		{
			nearest_point = mem;
			nearest_obj = list;
		}
		list = list->next;
	}
	if (nearest_obj == NULL)
		return (0x000000);
	return (get_color_obj(begin_list, nearest_obj, xy));
}*/

void	finish_calc_lights(int color_tab[3], double luminosity, \
		double specular)
{
	color_tab[0] = (int)fmin(color_tab[0] * luminosity + specular, 0xFF);
	color_tab[1] = (int)fmin(color_tab[1] * luminosity + specular, 0xFF);
	color_tab[2] = (int)fmin(color_tab[2] * luminosity + specular, 0xFF);
}

void	calc_lights(t_obj *list, t_obj *nearest_obj, int xy[2], \
				int color_tab[3])
{
	int		nb_spot;
	double	global_specular;
	double	global_luminosity;

	nb_spot = (int)list->nb_spot;
	global_specular = 0;
	global_luminosity = 0;
	while (--nb_spot >= 0)
	{
		if (shadows(list, xy, nearest_obj, nb_spot) == 1)
		{
			global_luminosity += calc_one_spot_luminosity(nearest_obj, nb_spot);
			global_specular = fmax(global_specular, \
				calc_one_spot_spec(nearest_obj, nb_spot));
		}
	}
	finish_calc_lights(color_tab, global_luminosity / (double)list->nb_spot, \
		global_specular);
}

int		get_color_obj(t_obj *list, t_obj *nearest_obj, int xy[2])
{
	int		color_tab[3];

	color_tab[0] = 0x0;
	color_tab[1] = 0x0;
	color_tab[2] = 0x0;
	get_color_tab(color_tab, nearest_obj);
	calc_lights(list, nearest_obj, xy, color_tab);
	return (color_tab[0] * 0x10000 + color_tab[1] * 0x100 + color_tab[2]);
}

void	get_color_tab(int color[3], t_obj *list)
{
	int	i;
	int	*color_tab;

	i = 0;
	color_tab = list->color_rgb;
	while (i < 3)
	{
		color[i] = *color_tab;
		color_tab++;
		i++;
	}
}

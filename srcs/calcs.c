/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 09:36:57 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/29 17:32:36 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

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
		if (shadows(list, xy, nearest_obj, nb_spot) == true)
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
	if (nearest_obj->reflection_id != 0 || nearest_obj->refraction_id != 0)
		calc_reflection_refraction(list, nearest_obj, color_tab);
	return (color_tab[0] * 0x10000 + color_tab[1] * 0x100 + color_tab[2]);
}

void	get_color_tab(int color[3], t_obj *list)
{
	int	i;
	int	*color_tab;

	i = 0;
	color_tab = NULL;
	if (list->texture)
	{
		texture(list, color);
		return ;
	}
	if (list->is_proc_texture == false)
		color_tab = list->color_rgb;
	else
		color_tab = get_proc_color(list);
	while (i < 3)
	{
		color[i] = *color_tab;
		color_tab++;
		i++;
	}
}

void	neg(double origin_tab[3], double new_tab[3])
{
	new_tab[0] = -origin_tab[0];
	new_tab[1] = -origin_tab[1];
	new_tab[2] = -origin_tab[2];
}

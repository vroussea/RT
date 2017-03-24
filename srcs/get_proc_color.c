/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_proc_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/14 15:32:24 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/16 16:10:48 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		*get_proc_cube(t_obj *obj)
{
	double			i;
	unsigned int	result;

	i = nearbyint((obj->intersec_point[0] + \
				obj->decal_xyz[0]) / 10);
	i += nearbyint((obj->intersec_point[1] + \
				obj->decal_xyz[1]) / 10);
	i += nearbyint((obj->intersec_point[2] + \
				obj->decal_xyz[2]) / 10);
	result = ((unsigned int)i) % 2;
	if (result == 0)
		return (obj->color1);
	return (obj->color2);
}

int		*get_proc_stripes(t_obj *obj)
{
	double	i;
	int		result;

	if (obj->proc_text_type == PROC_TEXT_STRAIGHT_STRIPES)
	{
		result = (int)(nearbyint((obj->intersec_point[1] + \
					obj->decal_xyz[1]) / 10));
	}
	else
	{
		i = ((obj->intersec_point[0] + \
					obj->decal_xyz[0]) / 10);
		i += ((obj->intersec_point[1] + \
					obj->decal_xyz[1]) / 10) + ((obj->intersec_point[2] + \
		obj->decal_xyz[2]) / 10);
		result = (int)nearbyint(i);
	}
	result %= 2;
	if (result == 0)
		return (obj->color1);
	return (obj->color2);
}

int		*get_proc_circle(t_obj *obj)
{
	double	i;
	int		result;

	i = 0;
	if (obj->proc_text_type != PROC_TEXT_CIRCLE_X)
		i += pow(((obj->intersec_point[0] + \
						obj->decal_xyz[0])) / 10, 2);
	if (obj->proc_text_type != PROC_TEXT_CIRCLE_Y)
		i += pow(((obj->intersec_point[1] + \
						obj->decal_xyz[1])) / 10, 2);
	if (obj->proc_text_type != PROC_TEXT_CIRCLE_Z)
		i += pow(((fabs(obj->intersec_point[2] + \
						obj->decal_xyz[2]))) / 10, 2);
	result = (int)(nearbyint(sqrt(i))) % 2;
	if (result == 0)
		return (obj->color1);
	return (obj->color2);
}

int		*get_proc_color(t_obj *obj)
{
	if (obj->proc_text_type >= PROC_TEXT_CIRCLE_X && \
			obj->proc_text_type <= PROC_TEXT_CIRCLE_Z)
		return (get_proc_circle(obj));
	else if (obj->proc_text_type == PROC_TEXT_DIAGONAL_STRIPES || \
			obj->proc_text_type == PROC_TEXT_STRAIGHT_STRIPES)
		return (get_proc_stripes(obj));
	else
		return (get_proc_cube(obj));
}
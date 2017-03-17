/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:15:05 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/17 15:12:37 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

bool		shadows(t_obj *list, int xy[2], t_obj *obj, int nb)
{
	double	point[3];
	double	vec[3];
	int		i;
	double	distance;

	i = 0;
	distance = obj->distance;
	while (i < 3)
	{
		vec[i] = (double)(list->base_pos_pixel_base[i]);
		vec[i] += xy[0] * list->base_vec_right[i] + xy[1] * \
					list->base_vec_down[i];
		vec[i] -= (double)(list->base_pos_cam[i]);
		point[i] = list->base_pos_cam[i] + vec[i] * distance;
		i++;
	}
	while (list != NULL)
	{
		if (obj != list && list->shadow(list, point, nb) == 0)
			return (false);
		list = list->next;
	}
	return (true);
}

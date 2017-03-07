/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:15:05 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/03 17:58:38 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		shadows(double distance, t_obj *list, int xy[2], t_obj *obj, int nb)
{
	double	point[3];
	double	vec[3];
	int		i;
	t_obj	*current;

	i = 0;
	while (i < 3)
	{
		vec[i] = (double)(list->base_pos_pixel_base[i]);
		vec[i] += xy[0] * list->base_vec_right[i] + xy[1] * list->base_vec_down[i];
		vec[i] -= (double)(list->base_pos_cam[i]);
		point[i] = list->base_pos_cam[i] + vec[i] * distance;
		i++;
	}
	current = list;
	while (current != NULL)
	{
		if (obj != current && calc_shadow_obj(current, point, nb) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

int		calc_shadow_obj(t_obj *ob, double point[3], int nb)
{
	return (ob->shadow(ob, point, nb));
}

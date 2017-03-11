# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    raytracer.cl                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/10 13:13:59 by vroussea          #+#    #+#              #
#    Updated: 2017/03/10 17:20:28 by vroussea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#include "../../include/rt.h"

__kernel void raytracer(__global int xy2[2], __global t_obj *begin_list, __global int *col)
{
	double	nearest_point;
	double	mem;
	t_obj	*nearest_obj;
	t_obj	*list;
	int		id;

	id = get_global_id(0);
	list = begin_list;
	nearest_obj = NULL;
	nearest_point = 2147483647;
	while (list != NULL)
	{
		if ((mem = get_intersec(xy, list)) < nearest_point)
		{
		nearest_point = mem;
		nearest_obj = list;
		}
		list = list->next;
	}
	if (nearest_obj == NULL)
		col = 0x000000;
	else
		col = get_color_obj(begin_list, nearest_obj, nearest_point, xy);
}

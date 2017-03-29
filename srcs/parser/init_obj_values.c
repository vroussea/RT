/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:37:00 by vroussea          #+#    #+#             */
/*   Updated: 2017/03/29 17:58:22 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	init_obj_values(t_obj *obj)
{
	obj->reflection_id = 0;
	obj->refraction_id = 0;
	obj->original_refraction = 1;
	obj->new_refraction = 1.5;
	obj->nb_ref = 0;
}

void	init_functs_obj2(t_obj *obj)
{
	if (obj->type == TYPE_CYLINDER)
	{
		obj->intersect = intersec_cylinder;
		obj->vector = get_vector_cylinder;
		obj->shadow = shadow_cylinder;
		obj->texturing = texture_cylinder;
	}
	else if (obj->type == TYPE_CONE)
	{
		obj->intersect = intersec_cone;
		obj->vector = get_vector_cone;
		obj->shadow = shadow_cone;
		obj->texturing = texture_cylinder;
	}
}

void	init_functs_obj(t_obj *obj)
{
	if (obj->type == TYPE_SPHERE)
	{
		obj->intersect = intersec_sphere;
		obj->vector = get_vector_sphere;
		obj->shadow = shadow_sphere;
		obj->texturing = texture_sphere;
	}
	else if (obj->type == TYPE_PLANE)
	{
		obj->intersect = intersec_plane;
		obj->vector = get_vector_plane;
		obj->shadow = shadow_plane;
		obj->texturing = texture_plane;
	}
	else
		init_functs_obj2(obj);
}

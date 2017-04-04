
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:37:00 by vroussea          #+#    #+#             */
/*   Updated: 2017/04/04 16:03:11 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	init_obj_values(t_obj *obj)
{
	obj->reflection_id = 0;
	obj->refraction_id = 0;
	obj->original_refraction = 1;
	obj->new_refraction = 1.5;
	obj->nb_ref = 0;
}

void	init_functs_obj(t_obj *obj)
{
	if (obj->type == TYPE_SPHERE)
		init_sphere_functs(obj);
	else if (obj->type == TYPE_PLANE)
		init_plane_functs(obj);
	else if (obj->type == TYPE_CONE)
		init_cone_functs(obj);
	else if (obj->type == TYPE_CYLINDER)
		init_cylinder_functs(obj);
}

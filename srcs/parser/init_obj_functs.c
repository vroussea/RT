/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_functs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboudrie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 18:43:02 by gboudrie          #+#    #+#             */
/*   Updated: 2017/04/04 16:04:33 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	init_sphere_functs(t_obj *obj)
{
	obj->intersect = intersec_sphere;
	obj->vector = get_vector_sphere;
	obj->shadow = shadow_sphere;
	obj->texturing = texture_sphere;
}

void	init_plane_functs(t_obj *obj)
{
	obj->intersect = intersec_plane;
	obj->vector = get_vector_plane;
	obj->shadow = shadow_plane;
	obj->texturing = texture_plane;
}

void	init_cylinder_functs(t_obj *obj)
{
	obj->intersect = intersec_cylinder;
	obj->vector = get_vector_cylinder;
	obj->shadow = shadow_cylinder;
	obj->texturing = texture_cylinder;
}

void	init_cone_functs(t_obj *obj)
{
	obj->intersect = intersec_cone;
	obj->vector = get_vector_cone;
	obj->shadow = shadow_cone;
	obj->texturing = texture_cylinder;
}

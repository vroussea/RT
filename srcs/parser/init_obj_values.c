/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 17:37:00 by vroussea          #+#    #+#             */
/*   Updated: 2017/03/24 18:29:40 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	init_obj_values(t_obj *obj)
{
	obj->reflection_id = 0;
	obj->refraction_id = 0;
	obj->original_refraction = 1;
	obj->new_refraction = 1;
}

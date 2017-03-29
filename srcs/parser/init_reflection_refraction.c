/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_reflection_refraction.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroussea <vroussea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 19:01:05 by vroussea          #+#    #+#             */
/*   Updated: 2017/03/24 19:25:43 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int	init_reflection_refraction(double *ref_id, char *line, char *balise)
{
	if (init_one_value(ref_id, line, balise) == true)
	{
		if (*ref_id < 0)
			*ref_id = 0;
		if (*ref_id > 100)
			*ref_id = 100;
		return (true);
	}
	return (false);
}

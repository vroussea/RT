/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 14:29:16 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/24 18:55:35 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static	void	get_vec_ray_cone(double vec_ray[3], t_obj *cone, int xy[2])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		vec_ray[i] = cone->pos_pixel_base[i];
		vec_ray[i] += xy[0] * cone->vec_right[i] + \
					xy[1] * cone->vec_down[i];
		vec_ray[i] -= cone->pos_cam[i];
		cone->base_vec_ray[i] = cone->base_pos_pixel_base[i];
		cone->base_vec_ray[i] += xy[0] * cone->base_vec_right[i] + \
			xy[1] * cone->base_vec_down[i];
		cone->base_vec_ray[i] -= cone->base_pos_cam[i];
		i++;
	}
}

void			abc_cone(double abc[3], double vec_ray[3], double base_pos[3], \
			double rad)
{
	abc[0] = pow(vec_ray[0], 2) + pow(vec_ray[1], 2) - \
		pow(vec_ray[2], 2) * pow(tan(rad), 2);
	abc[1] = 2 * (base_pos[0] * vec_ray[0] + base_pos[1] * vec_ray[1]\
		- base_pos[2] * vec_ray[2] * pow(tan(rad), 2));
	abc[2] = pow(base_pos[0], 2) + pow(base_pos[1], 2) - \
		pow(base_pos[2], 2) * pow(tan(rad), 2);
}

double			intersec_cone(int xy[2], t_obj *cone)
{
	double		vec_ray[3];
	double		abc[3];

	get_vec_ray_cone(vec_ray, cone, xy);
	abc[0] = pow(vec_ray[0], 2) + pow(vec_ray[1], 2) - \
		pow(vec_ray[2], 2) * pow(tan(cone->rad), 2);
	abc[1] = 2 * (cone->pos_cam[0] * vec_ray[0] + cone->pos_cam[1] * vec_ray[1]\
		- cone->pos_cam[2] * vec_ray[2] * pow(tan(cone->rad), 2));
	abc[2] = pow(cone->pos_cam[0], 2) + pow(cone->pos_cam[1], 2) - \
		pow(cone->pos_cam[2], 2) * pow(tan(cone->rad), 2);
	cone->distance = calc_2nd_degree_equation(abc);
	if (cone->distance != 2147483647)
		calc_intersec_point(cone, vec_ray);
	return (cone->distance);
}

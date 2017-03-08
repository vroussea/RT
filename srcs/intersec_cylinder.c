/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 14:29:16 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/08 19:55:15 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	get_vec_ray_cylinder(double vec_ray[3], t_obj *cylinder, int xy[2])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		vec_ray[i] = cylinder->pos_pixel_base[i];
		vec_ray[i] += xy[0] * cylinder->vec_right[i] + \
						xy[1] * cylinder->vec_down[i];
		vec_ray[i] -= cylinder->pos_cam[i];
		i++;
	}
}

void	abc_cylinder(double abc[3], double vec_ray[3], double base_pos[3], \
			double size)
{
	abc[0] = pow(vec_ray[0], 2) + pow(vec_ray[1], 2);
	abc[1] = 2 * (base_pos[0] * vec_ray[0] + \
		base_pos[1] * vec_ray[1]);
	abc[2] = pow(base_pos[0], 2) + pow(base_pos[1], 2) - \
		pow(size, 2);
}

double	intersec_cylinder(int xy[2], t_obj *cylinder)
{
	double		vec_ray[3];
	double		abc[3];

	get_vec_ray_cylinder(vec_ray, cylinder, xy);
	abc[0] = pow(vec_ray[0], 2) + pow(vec_ray[1], 2);
	abc[1] = 2 * (cylinder->pos_cam[0] * vec_ray[0] + \
			cylinder->pos_cam[1] * vec_ray[1]);
	abc[2] = pow(cylinder->pos_cam[0], 2) + pow(cylinder->pos_cam[1], 2) - \
			pow(cylinder->size, 2);
	cylinder->distance = calc_2nd_degree_equation(abc);
	if (cylinder->distance != 2147483647)
		calc_intersec_point(cylinder->intersec_point, \
			cylinder->distance, vec_ray, cylinder->pos_cam);
	return (cylinder->distance);
}

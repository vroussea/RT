/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 15:31:59 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/15 16:22:46 by vroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static void	get_vec_ray_sphere(double vec_ray[3], t_obj *sphere, int xy[2])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		vec_ray[i] = sphere->pos_pixel_base[i];
		vec_ray[i] += xy[0] * sphere->vec_right[i] + \
			xy[1] * sphere->vec_down[i];
		vec_ray[i] -= sphere->pos_cam[i];
		i++;
	}
}

void		abc_sphere(double abc[3], double vec_ray[3], double base_pos[3], \
			double size)
{
	abc[0] = pow(vec_ray[0], 2) + pow(vec_ray[1], 2) + pow(vec_ray[2], 2);
	abc[1] = 2 * (base_pos[0] * vec_ray[0] + base_pos[1] * \
			vec_ray[1] + base_pos[2] * vec_ray[2]);
	abc[2] = pow(base_pos[0], 2) + pow(base_pos[1], 2) + \
			pow(base_pos[2], 2) - pow(size, 2);
}

double		intersec_sphere(int xy[2], t_obj *sphere)
{
	double		vec_ray[3];
	double		abc[3];

	get_vec_ray_sphere(vec_ray, sphere, xy);
	abc[0] = pow(vec_ray[0], 2) + pow(vec_ray[1], 2) + pow(vec_ray[2], 2);
	abc[1] = 2 * (sphere->pos_cam[0] * vec_ray[0] + sphere->pos_cam[1] * \
			vec_ray[1] + sphere->pos_cam[2] * vec_ray[2]);
	abc[2] = pow(sphere->pos_cam[0], 2) + pow(sphere->pos_cam[1], 2) + \
			pow(sphere->pos_cam[2], 2) - pow(sphere->size, 2);
	sphere->distance = calc_2nd_degree_equation(abc);
	if (sphere->distance != 2147483647)
	{
		calc_intersec_point(sphere->intersec_point, \
			sphere->distance, vec_ray, sphere->pos_cam);
	}
	return (sphere->distance);
}

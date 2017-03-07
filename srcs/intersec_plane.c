/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 13:35:41 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/06 18:05:07 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static void		get_vec_ray_plane(double vec_ray[3], t_obj *plane, int xy[2])
{
	int i;

	i = 0;
	while (i < 3)
	{
		vec_ray[i] = plane->pos_pixel_base[i];
		vec_ray[i] += xy[0] * plane->vec_right[i] + \
			xy[1] * plane->vec_down[i];
		vec_ray[i] -= plane->pos_cam[i];
		i++;
	}
}

double			intersec_plane(int xy[2], t_obj *plane)
{
	double	vec_ray[3];
	double	ab[2];
	double	distance;

	get_vec_ray_plane(vec_ray, plane, xy);
	ab[0] = plane->norm_vec[0] * vec_ray[0] + plane->norm_vec[1] * \
			vec_ray[1] + plane->norm_vec[2] * vec_ray[2];
	if (ab[0] == 0)
		return (2147483647);
	ab[1] = plane->norm_vec[0] * plane->pos_cam[0] + \
		plane->norm_vec[1] * plane->pos_cam[1] + \
			plane->norm_vec[2] * plane->pos_cam[2] - plane->high;
	distance = (-ab[1]) / (ab[0]);
	if (distance > 0)
	{
		calc_intersec_point(plane->intersec_point, \
			distance, vec_ray, plane->pos_cam);
		return (distance);
	}
	return (2147483647);
}

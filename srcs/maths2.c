/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 16:32:01 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/29 17:33:44 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

double	radians(double degree)
{
	return (degree * (M_PI / 180.0));
}

void	normalize_vec(double vec[3])
{
	double	norm;
	int		i;

	norm = sqrt(pow(vec[0], 2) + pow(vec[1], 2) + pow(vec[2], 2));
	if (norm != 1)
	{
		i = 0;
		while (i < 3)
		{
			vec[i] = vec[i] / norm;
			i++;
		}
	}
}

double	calc_2nd_degree_equation(double abc[3])
{
	double	delta;
	double	ans;

	delta = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (delta == 0)
	{
		ans = -abc[1] / (2 * abc[0]);
		if (ans >= 1)
			return (ans);
	}
	if (delta > 0)
	{
		ans = (-abc[1] - sqrt(delta)) / (2 * abc[0]);
		if (ans > 0)
			return (ans);
		ans = (-abc[1] + sqrt(delta)) / (2 * abc[0]);
		if (ans > 0.01)
			return (ans);
	}
	return (2147483647);
}

void	calc_intersec_point(t_obj *obj, double vec_ray[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		obj->intersec_point[i] = obj->pos_cam[i] + vec_ray[i] * obj->distance;
		obj->base_intersec_point[i] = obj->base_pos_cam[i] + \
			obj->base_vec_ray[i] * obj->distance;
		i++;
	}
}

double	dot_product(double vec1[3], double vec2[3])
{
	return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

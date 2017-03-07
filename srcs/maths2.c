/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 16:32:01 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/06 18:04:59 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

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
		if (ans > 0)
			return (ans);
	}
	return (2147483647);
}

void	calc_intersec_point(double pos[3], double distance, double vec_ray[3], \
			double origin[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		pos[i] = origin[i] + vec_ray[i] * distance;
		i++;
	}
}

double	dot_product(double vec1[3], double vec2[3])
{
	return (vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]);
}

void	reflexion(double base_vec[3], double normal[3], double reflected_ray[3])
{
	int		i;
	double	d_product;

	normalize_vec(base_vec);
	normalize_vec(normal);
	d_product = dot_product(base_vec, normal);
	i = 0;
	while (i < 3)
	{
		reflected_ray[i] = 2 * d_product * normal[i] - base_vec[i];
		i++;
	}
}

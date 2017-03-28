/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 16:32:01 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/28 21:11:45 by eduwer           ###   ########.fr       */
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

void	reflection(double base_vec[3], double normal[3], \
		double reflected_ray[3])
{
	int		i;
	double	d_product;
	double	new_base_vec[3];

	normalize_vec(base_vec);
	normalize_vec(normal);
	new_base_vec[0] = -base_vec[0];
	new_base_vec[1] = -base_vec[1];
	new_base_vec[2] = -base_vec[2];
	d_product = dot_product(normal, new_base_vec);
	i = 0;
	while (i < 3)
	{
		reflected_ray[i] = base_vec[i] + ((2 * d_product) * normal[i]);
		i++;
	}
}

void	refraction(double base_vec[3], double normal[3], \
		double refracted_ray[3], t_obj *obj)
{
	int		i;
	double	d_product;
	double	d_product2;
	double	prod_refra;

	normalize_vec(base_vec);
	normalize_vec(normal);
	d_product = -dot_product(base_vec, normal);
	prod_refra = obj->original_refraction / obj->new_refraction;
	d_product2 = sqrt(1 - pow(prod_refra, 2) * (1 - pow(d_product, 2)));
	i = 0;
	while (i < 3)
	{
		refracted_ray[i] = prod_refra * base_vec[i];
		refracted_ray[i] += (prod_refra * d_product - d_product2) * normal[i];
		i++;
	}
}

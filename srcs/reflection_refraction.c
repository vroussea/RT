/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_refraction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:33:54 by eduwer            #+#    #+#             */
/*   Updated: 2017/04/12 16:13:02 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

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
	double	angle;
	double	n;
	double	c1;

	c1 = dot_product(base_vec, normal);
	if (c1 < 0)
	{
		c1 = c1 * (-1.0);
		n = obj->original_refraction / obj->new_refraction;
	}
	else
	{
		normal[0] = normal[0] * (-1.0);
		normal[1] = normal[1] * (-1.0);
		normal[2] = normal[2] * (-1.0);
		n = obj->new_refraction / obj->original_refraction;
	}
	angle = asin(n * sin(cos(c1 / (sqrt(dot_product(base_vec, base_vec) *
										dot_product(normal, normal))))));
	refracted_ray[0] = n * (base_vec[0] + c1 * normal[0]) -
		normal[0] * cos(angle);
	refracted_ray[1] = n * (base_vec[1] + c1 * normal[1]) -
		normal[1] * cos(angle);
	refracted_ray[2] = n * (base_vec[2] + c1 * normal[2]) -
		normal[2] * cos(angle);
}

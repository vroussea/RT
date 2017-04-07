/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_refraction.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:33:54 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/29 17:34:16 by eduwer           ###   ########.fr       */
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
	double	original_angle;
	double	new_angle;
	double	orth[3];

	normalize_vec(base_vec);
	normalize_vec(normal);
	original_angle = dot_product(base_vec, normal) /
	sqrt(dot_product(base_vec, base_vec) * dot_product(normal, normal));
	new_angle = asin(obj->original_refraction / obj->new_refraction *
		sin(original_angle));
	vect_prod(base_vec, normal, orth);
	refracted_ray[0] = normal[0];
	refracted_ray[1] = normal[1];
	refracted_ray[2] = normal[2];
	rotation(refracted_ray, orth, new_angle);
}

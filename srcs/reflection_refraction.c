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

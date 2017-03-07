/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:03:12 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/03 17:55:17 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	get_vector_sphere(double norm_vector[3], \
			double vec_light[3], t_obj *sphere, int nb)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		norm_vector[i] = sphere->intersec_point[i];
		vec_light[i] = (sphere->spot)[nb][i] - sphere->intersec_point[i];
		i++;
	}
	normalize_vec(norm_vector);
	normalize_vec(vec_light);
}

void	get_vector_plane(double norm_vector[3], \
			double vec_light[3], t_obj *plane, int nb)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		norm_vector[i] = plane->norm_vec[i];
		vec_light[i] = (plane->spot)[nb][i] - plane->intersec_point[i];
		i++;
	}
	normalize_vec(norm_vector);
	normalize_vec(vec_light);
}

void	get_vector_cylinder(double norm_vector[3], \
			double vec_light[3], t_obj *cylinder, int nb)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		norm_vector[i] = cylinder->intersec_point[i];
		vec_light[i] = (cylinder->spot)[nb][i] - cylinder->intersec_point[i];
		i++;
	}
	norm_vector[2] = 0;
	normalize_vec(norm_vector);
	normalize_vec(vec_light);
}

void	cross_product(double norm_vector[3], double vec1[3], double vec2[3])
{
	norm_vector[0] = vec1[1] * vec2[2] - vec2[1] * vec1[2];
	norm_vector[1] = vec1[2] * vec2[0] - vec2[2] * vec1[0];
	norm_vector[2] = vec1[0] * vec2[1] - vec2[0] * vec1[1];
	if ((vec1[2] > 0 && norm_vector[2] > 0) || \
		(vec1[2] < 0 && norm_vector[2] < 0))
	{
		norm_vector[0] = -norm_vector[0];
		norm_vector[1] = -norm_vector[1];
		norm_vector[2] = -norm_vector[2];
	}
}

void	get_vector_cone(double norm_vector[3], double vec_light[3], \
		t_obj *cone, int nb)
{
	int		i;
	double	vec1[3];
	double	vec2[3];

	i = 0;
	while (i < 3)
	{
		vec1[i] = cone->intersec_point[i];
		vec2[i] = cone->intersec_point[i];
		vec_light[i] = (cone->spot)[nb][i] - cone->intersec_point[i];
		i++;
	}
	vec2[2] = 0;
	rotation_z(vec2, 90);
	cross_product(norm_vector, vec1, vec2);
	normalize_vec(norm_vector);
	normalize_vec(vec_light);
}

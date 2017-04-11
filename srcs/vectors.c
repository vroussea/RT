/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:03:12 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/29 17:31:32 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

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
	ft_memcpy(sphere->n_normalz, norm_vector, sizeof(double[3]));
	if (sphere->is_waves == true)
		rotation_x(sphere->n_normalz, cos(sphere->intersec_point[0]) / 0.1);
	normalize_vec(norm_vector);
	normalize_vec(vec_light);
	if (sphere->is_waves == true)
		rotation_x(norm_vector, 10.0 * cos(sphere->intersec_point[0]));
	ft_memcpy(sphere->base_norm_vector, norm_vector, sizeof(double[3]));
	rotation_y(sphere->base_norm_vector, -(sphere->rotation[1]));
	rotation_x(sphere->base_norm_vector, -(sphere->rotation[0]));
	rotation_z(sphere->base_norm_vector, -(sphere->rotation[2]));
	rotation_y(sphere->n_normalz, -(sphere->rotation[1]));
	rotation_x(sphere->n_normalz, -(sphere->rotation[0]));
	rotation_z(sphere->n_normalz, -(sphere->rotation[2]));
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
	ft_memcpy(plane->n_normalz, norm_vector, sizeof(double[3]));
	if (plane->is_waves == true)
		rotation_y(plane->n_normalz, 2.0 * cos(plane->intersec_point[1]));
	normalize_vec(norm_vector);
	normalize_vec(vec_light);
	if (plane->is_waves == true)
		rotation_y(norm_vector, 2.0 * cos(plane->intersec_point[1]));
	ft_memcpy(plane->base_norm_vector, norm_vector, sizeof(double[3]));
	rotation_y(plane->base_norm_vector, -(plane->rotation[1]));
	rotation_x(plane->base_norm_vector, -(plane->rotation[0]));
	rotation_z(plane->base_norm_vector, -(plane->rotation[2]));
	rotation_y(plane->n_normalz, -(plane->rotation[1]));
	rotation_x(plane->n_normalz, -(plane->rotation[0]));
	rotation_z(plane->n_normalz, -(plane->rotation[2]));
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
	ft_memcpy(cylinder->n_normalz, norm_vector, sizeof(double[3]));
	if (cylinder->is_waves == true)
		rotation_z(cylinder->n_normalz, 2.0 * cos(cylinder->intersec_point[2]));
	normalize_vec(norm_vector);
	normalize_vec(vec_light);
	if (cylinder->is_waves == true)
		rotation_z(norm_vector, 2.0 * cos(cylinder->intersec_point[2]));
	ft_memcpy(cylinder->base_norm_vector, norm_vector, sizeof(double[3]));
	rotation_y(cylinder->base_norm_vector, -(cylinder->rotation[1]));
	rotation_x(cylinder->base_norm_vector, -(cylinder->rotation[0]));
	rotation_z(cylinder->base_norm_vector, -(cylinder->rotation[2]));
	rotation_y(cylinder->n_normalz, -(cylinder->rotation[1]));
	rotation_x(cylinder->n_normalz, -(cylinder->rotation[0]));
	rotation_z(cylinder->n_normalz, -(cylinder->rotation[2]));
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
	ft_memcpy(cone->n_normalz, norm_vector, sizeof(double[3]));
	if (cone->is_waves == true)
		rotation_z(cone->n_normalz, 1.5 * cos(cone->intersec_point[2]));
	normalize_vec(norm_vector);
	normalize_vec(vec_light);
	if (cone->is_waves == true)
		rotation_z(norm_vector, 1.5 * cos(cone->intersec_point[2]));
	ft_memcpy(cone->base_norm_vector, norm_vector, sizeof(double[3]));
	rotation_y(cone->base_norm_vector, -(cone->rotation[1]));
	rotation_x(cone->base_norm_vector, -(cone->rotation[0]));
	rotation_z(cone->base_norm_vector, -(cone->rotation[2]));
	rotation_y(cone->n_normalz, -(cone->rotation[1]));
	rotation_x(cone->n_normalz, -(cone->rotation[0]));
	rotation_z(cone->n_normalz, -(cone->rotation[2]));
}

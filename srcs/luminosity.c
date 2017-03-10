/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   luminosity.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 14:36:58 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/10 10:11:36 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

double	get_specular(double reflected_ray[3], double vec_light[3])
{
	double	tab[3];
	double	d_product;

	tab[0] = -vec_light[0];
	tab[1] = -vec_light[1];
	tab[2] = -vec_light[2];
	normalize_vec(reflected_ray);
	normalize_vec(tab);
	d_product = fmax(0, dot_product(tab, reflected_ray));
	return (0xFF * pow(d_product, 200));
}

void	getthegoodvector(t_obj *obj, double tab[3])
{
	double	*cam;
	double	*point;

	cam = obj->pos_cam;
	point = obj->intersec_point;
	tab[0] = point[0] - cam[0];
	tab[1] = point[1] - cam[1];
	tab[2] = point[2] - cam[2];
}

double	calc_one_spot_luminosity(t_obj *nearest_obj, int nb)
{
	double		norm_vector[3];
	double		vec_light[3];

	nearest_obj->vector(norm_vector, vec_light, nearest_obj, nb);
	return (fmax(dot_product(norm_vector, vec_light), 0));
}

double	calc_one_spot_spec(t_obj *nearest_obj, int nb)
{
	double	reflected_ray[3];
	double	vec_from_cam_to_point[3];
	double	norm_vector[3];
	double	vec_light[3];

	nearest_obj->vector(norm_vector, vec_light, nearest_obj, nb);
	reflexion(vec_light, norm_vector, reflected_ray);
	getthegoodvector(nearest_obj, vec_from_cam_to_point);
	return (get_specular(reflected_ray, vec_from_cam_to_point));
}

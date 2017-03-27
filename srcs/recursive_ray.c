/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 14:06:25 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/27 17:37:29 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	get_reflected_color(t_obj *list, t_obj *obj, int color[3]);
void	get_refracted_color(t_obj *list, t_obj *obj, int color[3]);

void	calc_reflection_refraction(t_obj *list, t_obj *obj, int color_tab[3])
{
	int			new_color[3];

	if (obj->reflection_id != 0)
	{
		get_reflected_color(list, obj, new_color);
		color_tab[0] = color_tab[0] * (1 - obj->reflection_id) + \
						new_color[0] * obj->reflection_id;
		color_tab[1] = color_tab[1] * (1 - obj->reflection_id) + \
						new_color[1] * obj->reflection_id;
		color_tab[2] = color_tab[2] * (1 - obj->reflection_id) + \
						new_color[2] * obj->reflection_id;
	}
	if (obj->refraction_id != 0)
	{
		get_refracted_color(list, obj, new_color);
		color_tab[0] = color_tab[0] * (1 - obj->refraction_id) + \
						new_color[0] * obj->refraction_id;
		color_tab[1] = color_tab[1] * (1 - obj->refraction_id) + \
						new_color[1] * obj->refraction_id;
		color_tab[2] = color_tab[2] * (1 - obj->refraction_id) + \
						new_color[2] * obj->refraction_id;
	}
}


void	get_reflected_color(t_obj *list, t_obj *obj, int color_tab[3])
{
	t_obj	*new_list;
	double	reflected_ray[3];
	int		color;

	reflection(obj->base_vec_ray, obj->base_norm_vector, reflected_ray);
	new_list = copy_the_list(list, obj, reflected_ray);
	color = calc_image(0, 0, new_list, NULL);
	color_tab[2] = color % 0x100;
	color /= 0x100;
	color_tab[1] = color % 0x100;
	color /= 0x100;
	color_tab[0] = color % 0x100;
}

void	get_refracted_color(t_obj *list, t_obj *obj, int color_tab[3])
{
	t_obj	*new_list;
	double	refracted_ray[3];
	int		color;

	refraction(obj->base_vec_ray, obj->base_norm_vector, refracted_ray, obj);
	new_list = copy_the_list(list, obj, refracted_ray);
	color = calc_image(0, 0, new_list, NULL);
	color_tab[2] = color % 0x100;
	color /= 0x100;
	color_tab[1] = color % 0x100;
	color /= 0x100;
	color_tab[0] = color % 0x100;

}

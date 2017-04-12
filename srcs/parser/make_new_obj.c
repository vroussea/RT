/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:16:23 by eduwer            #+#    #+#             */
/*   Updated: 2017/04/12 18:06:40 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_obj	*make_new_obj(t_obj *objs, int type)
{
	t_obj	*new_obj;

	if (objs->type == -1)
	{
		objs->type = type;
		objs->is_waves = false;
		objs->next = NULL;
		init_obj_values(objs);
		return (objs);
	}
	if ((new_obj = (t_obj *)malloc(sizeof(t_obj))) == NULL)
		return (NULL);
	while (objs->next != NULL)
		objs = objs->next;
	objs->next = new_obj;
	new_obj->type = type;
	new_obj->next = NULL;
	new_obj->is_waves = false;
	init_obj_values(new_obj);
	return (new_obj);
}

void	get_new_pos_cam(double pos_cam[3], double base_pos_cam[3], \
			double pos_obj[3])
{
	int	i;

	i = 0;
	if (pos_obj != NULL)
	{
		while (i < 3)
		{
			pos_cam[i] = base_pos_cam[i] - pos_obj[i];
			i++;
		}
	}
	else
	{
		while (i < 3)
		{
			pos_cam[i] = base_pos_cam[i];
			i++;
		}
	}
}

void	init_cam_obj(t_cam *cam, t_obj *obj)
{
	int		i;

	get_new_pos_cam(obj->pos_cam, cam->pos_cam, obj->pos);
	i = 0;
	while (i < 3)
	{
		obj->pos_pixel_base[i] = obj->pos_cam[i] + \
			cam->vec_cam[i] * 100 - obj->vec_right[i] / 2 - \
				obj->vec_down[i] / 2;
		obj->vec_right[i] /= cam->res[0];
		obj->vec_down[i] /= cam->res[1];
		i++;
	}
}

void	init_spot(t_obj *obj, t_cam *cam)
{
	int		i;
	Uint32	nb_spot;

	nb_spot = cam->nb_spot;
	if ((obj->spot = (double **)malloc(sizeof(double *) * nb_spot)) == NULL)
		ft_error("malloc", NULL);
	while (nb_spot-- > 0)
	{
		i = 0;
		if ((obj->spot[nb_spot] = malloc(sizeof(double) * 3)) == NULL)
			ft_error("malloc", NULL);
		while (i < 3)
		{
			obj->spot[nb_spot][i] = cam->spot[nb_spot][i];
			obj->spot[nb_spot][i] -= obj->pos[i];
			i++;
		}
		make_rotation(obj->spot[nb_spot], obj->rotation, 0);
	}
}

void	finish_init_obj(t_obj *obj, t_cam *cam)
{
	init_down_right(obj->vec_down, obj->vec_right, cam->rotation, cam->res);
	init_cam_obj(cam, obj);
	make_rotation(obj->pos_cam, obj->rotation, 0);
	make_rotation(obj->pos_pixel_base, obj->rotation, 0);
	make_rotation(obj->vec_right, obj->rotation, 0);
	make_rotation(obj->vec_down, obj->rotation, 0);
	init_spot(obj, cam);
	ft_memcpy(obj->base_pos_cam, cam->pos_cam, sizeof(cam->pos_cam));
	ft_memcpy(obj->base_pos_pixel_base, cam->pos_pixel_base, \
		sizeof(cam->pos_pixel_base));
	ft_memcpy(obj->base_vec_right, cam->vec_right, sizeof(cam->vec_right));
	ft_memcpy(obj->base_vec_down, cam->vec_down, sizeof(cam->vec_down));
	init_functs_obj(obj);
	if (obj->type == TYPE_PLANE)
		verif_plane_norm_vec(obj);
}

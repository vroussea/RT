/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_default_values.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 17:28:27 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/15 17:58:00 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	init_default_cam_values(t_cam *cam, int is_aa)
{
	int i;

	cam->pos_cam[0] = 600;
	cam->pos_cam[1] = 0;
	cam->pos_cam[2] = 50;
	cam->vec_cam[0] = -1;
	cam->vec_cam[1] = 0;
	cam->vec_cam[2] = 0;
	cam->res[0] = WIN_W + (WIN_W * is_aa * (AALEVEL - 1));
	cam->res[1] = WIN_HCAM + (WIN_HCAM * is_aa * (AALEVEL - 1));
	cam->vec_right[0] = 0;
	cam->vec_right[1] = 100;
	cam->vec_right[2] = 0;
	cam->vec_down[0] = 0;
	cam->vec_down[1] = 0;
	cam->vec_down[2] = -100.0 * ((double)WIN_HCAM / (double)WIN_W);
	i = -1;
	while (++i < 3)
	{
		cam->rotation[i] = 0;
		cam->pos_pixel_base[i] = cam->pos_cam[i] + cam->vec_cam[i] * 100 - \
								cam->vec_right[i] / 2 - cam->vec_down[i] / 2;
		cam->vec_right[i] /= cam->res[0];
		cam->vec_down[i] /= cam->res[1];
	}
}

void	init_default_sphere_values(t_cam *c, t_obj *o)
{
	o->pos[0] = 0;
	o->pos[1] = 0;
	o->pos[2] = 0;
	o->rotation[0] = 0;
	o->rotation[1] = 0;
	o->rotation[2] = 0;
	o->color_rgb[0] = 255;
	o->color_rgb[1] = 0;
	o->color_rgb[2] = 0;
	o->type = 0;
	o->size = 10;
	memcpy(o->pos_cam, c->pos_cam, sizeof(c->pos_cam));
	memcpy(o->res, c->res, sizeof(c->res));
	memcpy(o->pos_pixel_base, c->pos_pixel_base, \
		sizeof(c->pos_pixel_base));
	memcpy(o->vec_right, c->vec_right, sizeof(c->vec_right));
	memcpy(o->vec_down, c->vec_down, sizeof(c->vec_down));
	o->spot = NULL;
	o->is_proc_texture = false;
	o->nb_spot = c->nb_spot;
}

void	init_default_plane_values(t_cam *c, t_obj *o)
{
	o->norm_vec[0] = 0;
	o->norm_vec[1] = 0;
	o->norm_vec[2] = 1;
	o->pos[0] = 0;
	o->pos[1] = 0;
	o->pos[2] = 0;
	o->rotation[0] = 0;
	o->rotation[1] = 0;
	o->rotation[2] = 0;
	o->color_rgb[0] = 0;
	o->color_rgb[1] = 0;
	o->color_rgb[2] = 255;
	o->type = 1;
	o->high = 0;
	memcpy(o->pos_cam, c->pos_cam, sizeof(c->pos_cam));
	memcpy(o->res, c->res, sizeof(c->res));
	memcpy(o->pos_pixel_base, c->pos_pixel_base, \
		sizeof(c->pos_pixel_base));
	memcpy(o->vec_right, c->vec_right, sizeof(c->vec_right));
	memcpy(o->vec_down, c->vec_down, sizeof(c->vec_down));
	o->spot = NULL;
	o->is_proc_texture = false;
	o->nb_spot = c->nb_spot;
}

void	init_default_cylinder_values(t_cam *c, t_obj *o)
{
	o->pos[0] = 0;
	o->pos[1] = 0;
	o->pos[2] = 0;
	o->rotation[0] = 0;
	o->rotation[1] = 0;
	o->rotation[2] = 0;
	o->color_rgb[0] = 0;
	o->color_rgb[1] = 255;
	o->color_rgb[2] = 0;
	o->type = 2;
	o->size = 5;
	memcpy(o->pos_cam, c->pos_cam, sizeof(c->pos_cam));
	memcpy(o->res, c->res, sizeof(c->res));
	memcpy(o->pos_pixel_base, c->pos_pixel_base, \
		sizeof(c->pos_pixel_base));
	memcpy(o->vec_right, c->vec_right, sizeof(c->vec_right));
	memcpy(o->vec_down, c->vec_down, sizeof(c->vec_down));
	o->spot = NULL;
	o->is_proc_texture = false;
	o->nb_spot = c->nb_spot;
}

void	init_default_cone_values(t_cam *c, t_obj *o)
{
	o->pos[0] = 0;
	o->pos[1] = 0;
	o->pos[2] = 0;
	o->rotation[0] = 0;
	o->rotation[1] = 0;
	o->rotation[2] = 0;
	o->color_rgb[0] = 255;
	o->color_rgb[1] = 255;
	o->color_rgb[2] = 0;
	o->type = 3;
	o->angle = 45;
	memcpy(o->pos_cam, c->pos_cam, sizeof(c->pos_cam));
	memcpy(o->res, c->res, sizeof(c->res));
	memcpy(o->pos_pixel_base, c->pos_pixel_base, \
		sizeof(c->pos_pixel_base));
	memcpy(o->vec_right, c->vec_right, sizeof(c->vec_right));
	memcpy(o->vec_down, c->vec_down, sizeof(c->vec_down));
	o->spot = NULL;
	o->is_proc_texture = false;
	o->nb_spot = c->nb_spot;
}

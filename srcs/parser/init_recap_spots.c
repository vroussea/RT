/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_recap_spots.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:23:30 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/18 18:25:10 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void	get_plane_high(t_obj *plane, t_cam *cam)
{
	plane->high = plane->norm_vec[0] * cam->pos_pixel_base[0] + \
					plane->norm_vec[1] * cam->pos_pixel_base[1] + \
					plane->norm_vec[2] * cam->pos_pixel_base[2];
}

void	init_recap_spots(t_obj *obj, t_cam *cam)
{
	//double	**recap_tab;
	double	distance;
	t_obj	plane;
	int		xy[2];
	int		i;
	int		nb_spot;
	int		n;
	double	x_y[2];
	obj = NULL;

	nb_spot = 0;
	while (nb_spot < (int)cam->nb_spot)
	{
		i = 0;
		xy[0] = 0;
		xy[1] = 0;
		while (i < 3)
		{
			plane.pos_pixel_base[i] = cam->spot[nb_spot][i];
			plane.pos_cam[i] = cam->pos_cam[i];
			plane.norm_vec[i] = cam->vec_cam[i];
			i++;
		}
		get_plane_high(&plane, cam);
		if ((distance = intersec_plane(xy, &plane)) != 2147483647)
		{
			n = 0;
			while ((cam->vec_down[(n + 1) % 3] * cam->vec_right[n] - \
			 cam->vec_down[n] * cam->vec_right[(n + 1) % 3]) == 0 && n < 3)
				n++;
			x_y[1] = nearbyint((cam->vec_right[n] * \
			(plane.intersec_point[(n + 1) % 3] - cam->pos_pixel_base[(n + 1) % 3]) + \
			cam->vec_right[(n + 1) % 3] * \
			(cam->pos_pixel_base[n] - plane.intersec_point[n])) / \
			(cam->vec_down[(n + 1) % 3] * cam->vec_right[n] - \
			 cam->vec_down[n] * cam->vec_right[(n + 1) % 3]));
			n = 0;
			while (cam->vec_right[n] == 0)
				n++;
			x_y[0] = nearbyint((plane.intersec_point[n] - \
			cam->pos_pixel_base[n] - x_y[1] * cam->vec_down[n]) / \
			cam->vec_right[n]);
			printf ("%f, %f\n", x_y[0], x_y[1]);
		}
		nb_spot++;
	}
}

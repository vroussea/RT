/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_recap_spots.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/18 16:23:30 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/29 17:27:49 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	get_plane_high(t_obj *plane, t_cam *cam)
{
	plane->high = plane->norm_vec[0] * cam->pos_pixel_base[0] + \
					plane->norm_vec[1] * cam->pos_pixel_base[1] + \
					plane->norm_vec[2] * cam->pos_pixel_base[2];
}

void	remalloc_recap_spot(t_obj *obj, double xy[2], t_obj *plane)
{
	double			**recap_spot;
	unsigned int	nb_spot;
	double			distance;

	if ((recap_spot = (double **)malloc(sizeof(double *) * \
		obj->nb_spots_on_screen)) == NULL)
		ft_error("malloc", NULL);
	nb_spot = 0;
	while (nb_spot < obj->nb_spots_on_screen - 1)
	{
		recap_spot[nb_spot] = obj->recap_spots[nb_spot];
		++nb_spot;
	}
	if ((recap_spot[nb_spot] = (double *)malloc(sizeof(double) * 6)) == NULL)
		ft_error("malloc", NULL);
	memcpy(&(recap_spot[nb_spot][0]), xy, sizeof(double[2]));
	memcpy(&(recap_spot[nb_spot][3]), plane->pos_pixel_base, \
		sizeof(plane->pos_pixel_base));
	distance = sqrt(pow(plane->pos_pixel_base[0] - plane->pos_cam[0], 2) + \
		pow(plane->pos_pixel_base[1] - plane->pos_cam[1], 2) + \
		pow(plane->pos_pixel_base[2] - plane->pos_cam[2], 2));
	recap_spot[nb_spot][2] = distance;
	free(obj->recap_spots);
	obj->recap_spots = recap_spot;
}

void	external(t_cam *cam, double *x_y, t_obj *plane, t_obj *obj)
{
	int	n;

	n = 0;
	while ((cam->vec_down[(n + 1) % 3] * cam->vec_right[n] - \
	cam->vec_down[n] * cam->vec_right[(n + 1) % 3]) == 0 && n < 3)
		n++;
	x_y[1] = nearbyint((cam->vec_right[n] * \
			(plane->intersec_point[(n + 1) % 3] - \
	cam->pos_pixel_base[(n + 1) % 3]) + cam->vec_right[(n + 1) % 3] * \
	(cam->pos_pixel_base[n] - plane->intersec_point[n])) / \
	(cam->vec_down[(n + 1) % 3] * cam->vec_right[n] - \
	cam->vec_down[n] * cam->vec_right[(n + 1) % 3]));
	n = 0;
	while (nearbyint(cam->vec_right[n] * 100000) == 0)
		n++;
	x_y[0] = nearbyint((plane->intersec_point[n] - \
	cam->pos_pixel_base[n] - x_y[1] * cam->vec_down[n]) / \
	cam->vec_right[n]);
	if (x_y[0] >= 0 && x_y[1] >= 0 && \
		x_y[0] <= cam->res[0] && x_y[1] <= cam->res[1])
	{
		(obj->nb_spots_on_screen)++;
		remalloc_recap_spot(obj, x_y, plane);
	}
}

void	externalplus(int *n, t_cam *cam, t_obj *plane, int *nb_spot)
{
	plane->pos_pixel_base[*n] = cam->spot[nb_spot[0]][*n];
	plane->pos_cam[*n] = cam->pos_cam[*n];
	plane->norm_vec[*n] = cam->vec_cam[*n];
	(n[0])++;
}

void	init_recap_spots(t_obj *obj, t_cam *cam)
{
	t_obj	plane;
	int		xy[2];
	int		nb_spot;
	int		n;
	double	x_y[2];

	nb_spot = 0;
	obj->nb_spots_on_screen = 0;
	obj->recap_spots = NULL;
	while (nb_spot < (int)cam->nb_spot)
	{
		n = 0;
		xy[0] = 0;
		xy[1] = 0;
		while (n < 3)
		{
			externalplus(&n, cam, &plane, &nb_spot);
		}
		get_plane_high(&plane, cam);
		if (intersec_plane(xy, &plane) != 2147483647)
		{
			external(cam, x_y, &plane, obj);
		}
		nb_spot++;
	}
}

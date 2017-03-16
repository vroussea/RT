/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 17:32:14 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/15 16:27:06 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

static bool	init_cam_pos_rotation(int fd, t_cam *cam)
{
	int		ret_gnl;
	char	*line;

	while ((ret_gnl = get_next_line(fd, &line) == 1) && \
			strstr(line, "</cam>") == NULL)
	{
		if (strstr(line, "<pos>") != NULL && \
				init_3_values(cam->pos_cam, line, "</pos>") == true)
			return (true);
		else if (strstr(line, "<rotation>") != NULL && \
				init_3_values(cam->rotation, line, "</rotation>") == true)
			return (true);
		free(line);
	}
	free(line);
	if (ret_gnl != 1)
		return (true);
	return (false);
}

void		init_down_right(double vec_down[3], double vec_right[3], \
			double rotation[3], int res[2])
{
	vec_right[0] = 0;
	vec_right[1] = 100;
	vec_right[2] = 0;
	make_rotation(vec_right, rotation);
	vec_down[0] = 0;
	vec_down[1] = 0;
	vec_down[2] = -100.0 / ((double)res[0] / (double)res[1]);
	make_rotation(vec_down, rotation);
}

static bool	finish_init_cam(t_cam *cam)
{
	int		i;

	init_down_right(cam->vec_down, cam->vec_right, cam->rotation, cam->res);
	make_rotation(cam->vec_cam, cam->rotation);
	i = 0;
	while (i < 3)
	{
		cam->pos_pixel_base[i] = cam->pos_cam[i] + cam->vec_cam[i] * 100 - \
			cam->vec_right[i] / 2 - cam->vec_down[i] / 2;
		cam->vec_right[i] /= cam->res[0];
		cam->vec_down[i] /= cam->res[1];
		i++;
	}
	if (cam->nb_spot == 0)
		return(init_one_spot(cam));
	return (false);
}

bool		get_cam_infos(int fd, t_cam *cam, int is_aa)
{
	int		ret_gnl;
	char	*line;

	cam->nb_spot = 0;
	cam->spot = NULL;
	init_default_cam_values(cam, is_aa);
	while ((ret_gnl = get_next_line(fd, &line)) == 1 && \
			strstr(line, "</cam_infos>") == NULL)
	{
		if (strstr(line, "<cam>") != NULL && \
				init_cam_pos_rotation(fd, cam) == true)
			return (true);
		else if (strstr(line, "<spots>") != NULL && \
				init_spots(fd, cam) == true)
			return (true);
		free(line);
	}
	free(line);
	if (ret_gnl != 1)
		return (true);
	return (finish_init_cam(cam));
}

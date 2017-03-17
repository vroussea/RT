/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_spots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 17:31:07 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/16 16:18:07 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

bool	init_and_copy(double **list_spot, char *line, t_cam *cam)
{
	unsigned int i;

	if ((list_spot = (double **)malloc(sizeof(double *) * \
					cam->nb_spot)) == NULL)
		return (true);
	if ((list_spot[cam->nb_spot - 1] = \
				(double *)malloc(sizeof(double) * 3)) == NULL)
		return (true);
	if (init_3_values(list_spot[cam->nb_spot - 1], line, "</pos>") == true)
		return (true);
	i = 0;
	while (i < cam->nb_spot - 1)
	{
		list_spot[i] = cam->spot[i];
		i++;
	}
	free(cam->spot);
	cam->spot = list_spot;
	return (false);
}

bool	init_one_spot(t_cam *cam)
{
	cam->nb_spot = 1;
	if ((cam->spot = (double **)malloc(sizeof(double *) * \
					cam->nb_spot)) == NULL)
		return (true);
	if ((cam->spot[0] = (double *)malloc(sizeof(double) * 3)) == NULL)
		return (true);
	cam->spot[0][0] = (double)400;
	cam->spot[0][1] = (double)0;
	cam->spot[0][2] = (double)100;
	return (false);
}

bool	init_spots(int fd, t_cam *cam)
{
	int		ret_gnl;
	double	**list_spot;
	char	*line;

	list_spot = NULL;
	while ((ret_gnl = get_next_line(fd, &line) == 1) && \
			strstr(line, "</spots>") == NULL)
	{
		if (strstr(line, "<pos>") != NULL)
		{
			cam->nb_spot++;
			if (init_and_copy(list_spot, line, cam) == true)
				return (true);
		}
		free(line);
	}
	free(line);
	if (ret_gnl != 1)
		return (true);
	return (false);
}

void	add_spots_to_scene(t_cam *cam, t_obj *objs)
{
	unsigned int	i;
	t_obj			*spot;

	i = 0;
	while (i < cam->nb_spot)
	{
		if ((spot = make_new_obj(objs, TYPE_SPOT)) == NULL)
			ft_error("malloc", NULL);
		memcpy(spot->pos, (cam->spot)[i], sizeof(spot->pos));
		spot->rotation[0] = 0;
		spot->rotation[1] = 0;
		spot->rotation[2] = 0;
		spot->size = 5;
		spot->is_proc_texture = false;
		spot->nb_spot = 0;
		spot->color_rgb[0] = 0xFF;
		spot->color_rgb[1] = 0xFF;
		spot->color_rgb[2] = 0xFF;
		finish_init_obj(spot, cam);
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_spots.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 17:31:07 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/03 17:51:13 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		init_and_copy(double **list_spot, char *line, t_cam *cam)
{
	unsigned int i;

	if ((list_spot = (double **)malloc(sizeof(double *) * cam->nb_spot)) == NULL)
		return (-1);
	if ((list_spot[cam->nb_spot - 1] = \
				(double *)malloc(sizeof(double) * 3)) == NULL)
		return (-1);
	if (init_3_values(list_spot[cam->nb_spot - 1], line ,"</pos>") == -1)
		return (-1);
	i = 0;
	while (i < cam->nb_spot - 1)
	{
		list_spot[i] = cam->spot[i];
		i++;
	}
	free(cam->spot);
	cam->spot = list_spot;
	return (0);
}

int		init_one_spot(t_cam *cam, double **list_spot)
{
	cam->nb_spot = 1;
	if ((list_spot = (double **)malloc(sizeof(double *) * cam->nb_spot)) == NULL)
		return (-1);
	if ((list_spot[0] = (double *)malloc(sizeof(double) * 3)) == NULL)
		return (-1);
	list_spot[0][0] = (double)400;
	list_spot[0][1] = (double)0;
	list_spot[0][2] = (double)100;
	return (0);
}

int		init_spots(int fd, t_cam *cam)
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
			if (init_and_copy(list_spot, line, cam) == -1)
				return (-1);
		}
		free(line);
	}
	free(line);
	if (ret_gnl != 1)
		return (-1);
	if (cam->nb_spot == 0)
		return (init_one_spot(cam, list_spot));
	return (0);
}
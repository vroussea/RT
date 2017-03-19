/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 17:21:14 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/19 16:53:38 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		free_recap_spot(t_obj *list)
{
	unsigned int i;

	i = 0;
	while (i < list->nb_spots_on_screen)
		free(list->recap_spots[i++]);
	free(list->recap_spots);
}

void		del_all_list(t_obj *list)
{
	t_obj			*mem;
	int				nb_spot;

	mem = list;
	free_recap_spot(list);
	while (list != NULL)
	{
		mem = list->next;
		nb_spot = (int)(list->nb_spot);
		while (--nb_spot >= 0)
			free(list->spot[nb_spot]);
		free(list->spot);
		free(list);
		list = mem;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 17:21:14 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/16 14:33:12 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

void		del_all_list(t_obj *list)
{
	t_obj			*mem;
	int				nb_spot;

	mem = list;
	while (list != NULL)
	{
		mem = list->next;
		nb_spot = (int)(list->nb_spot);
		while (--nb_spot >= 0 && list->type != TYPE_SPOT)
			free(list->spot[nb_spot]);
		if (list->type != TYPE_SPOT)
			free(list->spot);
		free(list);
		list = mem;
	}
}

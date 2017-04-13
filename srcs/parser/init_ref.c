/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ref.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 16:26:23 by eduwer            #+#    #+#             */
/*   Updated: 2017/04/13 14:45:42 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

bool	init_ref(double *ref, char *line, char *balise)
{
	if (init_one_value(ref, line, balise) == true)
		return (true);
	*ref = (fmin(fmax(0, *ref), 100)) / 100.0;
	return (false);
}

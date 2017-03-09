/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 10:57:53 by pfichepo          #+#    #+#             */
/*   Updated: 2017/02/01 10:57:54 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	updatepixel(t_envgui *env, int x, int y, Uint32 color)
{
	double	v;
	int		nb;

	nb = y;
	if (env->aa)
	{
		putpixel(env->raysurfaceaa, x, y, color);
		env->aaupdated = 1;
		v = math_remapsimple(nb, env->raysurfaceaa->h, 1);
	}
	else
	{
		putpixel(env->raysurface, x, y, color);
		v = math_remapsimple(nb, env->raysurface->h, 1);
	}
	env->isloading = (nb != env->w * env->h);
	env->loadingvalue = v;
	env->drag = 0;
}

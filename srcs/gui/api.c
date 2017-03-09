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
	env->aaupdated = env->aa;
	putpixel(env->raysurface[env->aa], x, y, color);
	v = math_remapsimple(nb, env->raysurface[env->aa]->h, 1);
	env->isloading = (nb != env->w * env->h);
	env->loadingvalue = v;
	env->drag = 0;
}

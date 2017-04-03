/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:15:59 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/29 17:38:36 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>
#include <rt.h>
#include <SDL_image.h>

t_threaddata	*mallocit(Uint8 id, t_envgui *env)
{
	t_threaddata *ret;

	ret = (t_threaddata*)malloc(sizeof(t_threaddata));
	ret->threadid = id;
	ret->aa = env->aa;
	ret->image = env->raysurface[env->aa];
	if (env->fog)
		ret->fogmap = env->zraysurface[env->aa];
	else
		ret->fogmap = NULL;
	if (id == 1)
		ret->loading = &(env->loadingvalue);
	return (ret);
}

void			draw_the_image(char **argv, t_envgui *env)
{
	t_parserdata	*data;
	t_obj			*belst;

	SDL_SetCursor(env->wait);
	get_infos(argv[1], &belst, env->aa);
	data = (t_parserdata*)malloc(sizeof(t_parserdata));
	data->thread1 = mallocit(1, env);
	data->thread2 = mallocit(2, env);
	data->thread3 = mallocit(3, env);
	data->thread4 = mallocit(4, env);
	env->isloading = 1;
	get_infos(argv[1], &(data->thread1->data), env->aa);
	get_infos(argv[1], &(data->thread2->data), env->aa);
	get_infos(argv[1], &(data->thread3->data), env->aa);
	get_infos(argv[1], &(data->thread4->data), env->aa);
	initthreads(data);
	env->aaupdated = env->aa;
	if (env->fog)
		SDL_BlitSurface(env->zraysurface[env->aa], NULL,\
			env->raysurface[env->aa], NULL);
	if (env->flares)
		processflares(env->raysurface[env->aa], belst,\
			env->flare, 1 + ((AALEVEL - 1) * env->aa));
	env->isloading = 0;
	SDL_SetCursor(env->arrow);
}

int				calc_image(int x, int y, t_obj *begin_list, SDL_Surface *fogmap)
{
	double	nearest_point;
	double	mem;
	t_obj	*nearest_obj;
	t_obj	*list;
	int		xy[2];

	xy[0] = x;
	xy[1] = y;
	list = begin_list;
	nearest_obj = NULL;
	nearest_point = 2147483647;
	while (list != NULL)
	{
		if ((mem = list->intersect(xy, list)) < nearest_point)
		{
			nearest_point = mem;
			nearest_obj = list;
			putpixel(fogmap, x, y, rgbafog(mem));
		}
		list = list->next;
	}
	putpixel(fogmap, x, y, rgbafog(FOGO));
	if (nearest_obj == NULL)
		return (0x000000);
	return (get_color_obj(begin_list, nearest_obj, xy));
}

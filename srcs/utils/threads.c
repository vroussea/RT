/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 09:13:25 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/29 17:30:38 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <rtv1.h>
#include <time.h>

int			threadsavepic(void *adr)
{
	SDL_Surface	*image;
	char		*buff;

	image = (SDL_Surface*)adr;
	buff = (char *)malloc(sizeof(char) * 40);
	sprintf(buff, "%d.bmp", (int)time(NULL));
	SDL_SaveBMP(image, buff);
	free(buff);
	return (0);
}

static int	ret(t_threaddata *data)
{
	del_all_list(data->data);
	free(data);
	return (data->threadid);
}

static int	threadthink(void *d)
{
	t_threaddata	*data;
	int				xy[2];
	int				xmax;
	int				ymax;
	int				i;

	i = 0;
	data = (t_threaddata*)d;
	xmax = data->data->res[0];
	ymax = data->data->res[1];
	xy[0] = data->threadid - 1;
	while (xy[0] < xmax)
	{
		xy[1] = 0;
		while (xy[1] < ymax)
		{
			putpixel(data->image, xy[0], xy[1], \
				(Uint32)calc_image(xy[0], xy[1], data->data, data->fogmap));
			if (data->threadid == 1)
				*(data->loading) = math_remapsimple(i++ * 4, ymax * xmax, 1);
			xy[1]++;
		}
		xy[0] += 4;
	}
	return (ret(data));
}

void		initthreads(t_parserdata *data)
{
	SDL_Thread *thread1;
	SDL_Thread *thread2;
	SDL_Thread *thread3;
	SDL_Thread *thread4;

	thread1 = SDL_CreateThread(threadthink, "Thread1", (void*)(data->thread1));
	thread2 = SDL_CreateThread(threadthink, "Thread2", (void*)(data->thread2));
	thread3 = SDL_CreateThread(threadthink, "Thread3", (void*)(data->thread3));
	thread4 = SDL_CreateThread(threadthink, "Thread4", (void*)(data->thread4));
	SDL_WaitThread(thread1, NULL);
	SDL_WaitThread(thread2, NULL);
	SDL_WaitThread(thread3, NULL);
	SDL_WaitThread(thread4, NULL);
}

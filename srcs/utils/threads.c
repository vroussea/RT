/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 09:13:25 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/15 09:13:27 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <rtv1.h>

static int threadthink(void *d)
{
	t_threaddata 	*data;

	int 			xy[2];

	data = (t_threaddata*)d;

	xy[0] = 0;
	xy[1] = 0;
	printf("%s, %i\n", "bite", data->threadid);
	while (xy[0] < (WIN_W + (WIN_W * data->aa * (AALEVEL - 1))))
	{
		xy[1] = 0;
		while (xy[1] < (WIN_HCAM + (WIN_HCAM * data->aa * (AALEVEL - 1))))
		{
			if (xy[0]%4 == data->threadid-1)
			{
				putpixel(data->image, xy[0], xy[1],(Uint32)calc_image(xy, data->data));
			}
			xy[1]++;
		}
		xy[0]++;

	}
	return (data->threadid);
}



void initthreads(t_parserdata *data)
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
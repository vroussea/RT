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

static int getx(int id, bool aa)
{
	if (id%2)
		return (0);
	if (aa)
		return (WIN_W * AALEVEL)/2;
	else
		return (WIN_W)/2;
}

static int gety(int id, bool aa)
{
	if (id < 3)
		return (0);
	if (aa)
		return (WIN_HCAM * AALEVEL)/2;
	else
		return (WIN_HCAM)/2;
}



static int threadthink(void *d)
{
	t_threaddata 	*data;

	int 			xy[2];
	int 			xy2[2];
	int 			ymax;
	int 			xmax;
	int 			xoff;
	int 			yoff;
	int 			mult;

	data = (t_threaddata*)d;
	if (data->aa)
		mult = AALEVEL;
	else
		mult = 1;
	xmax = (WIN_W * mult)/2;
	ymax = (WIN_HCAM * mult)/2;
	xoff = getx(data->threadid, data->aa);
	yoff = gety(data->threadid, data->aa);
	printf("Thread : %i with offsets -> X : %i  Y : %i\n", data->threadid, xoff, yoff);
	xy[0] = 0;
	xy[1] = 0;
	int i = 0;
	while (xy[0] < xmax)
	{
		xy[1] = 0;
		while (xy[1] < ymax)
		{
			xy2[0] = xy[0]+xoff;
			xy2[1] = xy[1]+yoff;
			putpixel(data->image, xy2[0], xy2[1],(Uint32)calc_image(xy2, data->data));
			if (data->threadid == 1)
			{
				i++;
				*(data->loading) = math_remapsimple(i, ymax * xmax, 1);
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
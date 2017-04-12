/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 10:23:25 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/09 10:23:27 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void	startdrag(t_envgui *e, int press, int y)
{
	if (e->drag && press == 0)
		e->drag = 0;
	if (y < 33)
	{
		e->drag = press;
		SDL_GetGlobalMouseState(&e->dragx, &e->dragy);
	}
}


static char *gettype(int type)
{
	if (type == TYPE_PLANE )
		return ("Plane");
	if (type == TYPE_SPHERE )
		return ("Sphere");
	if (type == TYPE_CONE )
		return ("Cone");
	if (type == TYPE_CYLINDER)
		return ("Cylindre");
	return ("Plane");
}

static void infopixel(int x, int y, t_obj *begin_list)
{
	double	nearest_point;
	double	mem;
	t_obj	*nearest_obj;
	t_obj	*list;
	int		xy[2];
	int i = 0;
	int foundi = 0;

	xy[0] = x;
	xy[1] = y;

	printf("%s\n", "---NewClick---");
	list = begin_list;
	nearest_obj = NULL;
	nearest_point = 2147483647;
	while (list != NULL)
	{
		mem = list->intersect(xy, list);
		if (mem  < nearest_point)
		{
			nearest_point = mem;
			nearest_obj = list;
			foundi = i;
		}
		list = list->next;
		i++;
	}
	if (nearest_obj) // si on trouve un objet
	{

		if (nearest_obj->refraction_id == 0) 
			printf("Found objet at %i:%i with ID %i| Type is %s and dist is %f\n",x ,y,foundi, gettype(nearest_obj->type), nearest_point);
		else // si l'objet trouvé est un objet qui refract, on fait rebondire le rayon
		{
			i = 0;
			foundi = i;
			t_obj	*new_list;
			double	refracted_ray[3];
			double		norm_vector[3];
			double		vec_light[3];
		

			nearest_obj->vector(norm_vector, vec_light, nearest_obj, 1);

			refraction(nearest_obj->base_vec_ray, nearest_obj->n_normalz, refracted_ray, nearest_obj);
			new_list = copy_the_list(begin_list, nearest_obj, refracted_ray);
			
			xy[0] = 0;
			xy[1] = 0;
			list = new_list;
			nearest_obj = NULL;
			nearest_point = 2147483647;
			while (list != NULL)
			{
				mem = list->intersect(xy, list);
				printf("[REFRACT]Dist of %s is %f \n",gettype(list->type),mem );
				if (mem  < nearest_point)
				{
					nearest_point = mem;
					nearest_obj = list;
					foundi = i;
				}
				list = list->next;
				i++;
			}
			if (nearest_obj)
				printf("[REFRACT]Found objet at %i:%i with ID %i| Type is %s and dist is %f\n",x ,y,foundi, gettype(nearest_obj->type), nearest_point);
			else
				printf("[REFRACT]No object found at %i:%i inside refraction\n", x,y);

		}


	}
	else
		printf("No object found at %i:%i\n", x,y);

	del_all_list(begin_list);
}



void		mouse_press(SDL_Event *ev, int press, t_envgui *e)
{
	t_button	*button;
	int			x;
	int			y;
	t_obj 		*obj;

	obj = NULL;
	x = ev->button.x;
	y = ev->button.y;
	if (press)
	{
		get_infos("scenes/demo3notext.xml",&obj ,0);
		infopixel(x, y-35, obj);
	}
	if (press == 0 && e->lastpressed && (e->currentbutton != e->lastpressed))
		e->lastpressed->pressed = 0;
	if (e->currentbutton)
	{
		button = e->currentbutton;
		if (press)
		{
			button->pressed = 1;
			e->lastpressed = e->currentbutton;
		}
		else
		{
			if (e->currentbutton == e->lastpressed)
				button->pressfunc(e, button);
			button->pressed = 0;
		}
	}
	else
		startdrag(e, press, y);
}

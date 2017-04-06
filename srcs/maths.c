/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 18:59:08 by eduwer            #+#    #+#             */
/*   Updated: 2017/02/16 16:31:27 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	rotation_x(double vec[3], double degree)
{
	double b;
	double c;
	double rad;

	rad = radians(degree);
	b = vec[1];
	c = vec[2];
	vec[1] = b * cos(rad) + c * sin(rad);
	vec[2] = b * -sin(rad) + c * cos(rad);
}

void	rotation_y(double vec[3], double degree)
{
	double a;
	double c;
	double rad;

	rad = radians(degree);
	a = vec[0];
	c = vec[2];
	vec[0] = a * cos(rad) - c * sin(rad);
	vec[2] = a * sin(rad) + c * cos(rad);
}

void	rotation_z(double vec[3], double degree)
{
	double a;
	double b;
	double rad;

	rad = radians(degree);
	a = vec[0];
	b = vec[1];
	vec[0] = a * cos(rad) + b * sin(rad);
	vec[1] = a * (-sin(rad)) + b * cos(rad);
}

void	make_rotation(double vec[3], double rotation[3])
{
	if (rotation != NULL)
	{
		if (rotation[2] != 0)
			rotation_z(vec, rotation[2]);
		if (rotation[0] != 0)
			rotation_x(vec, rotation[0]);
		if (rotation[1] != 0)
			rotation_y(vec, rotation[1]);
	}
}

void	rotation(double vect[3], double axe[3], double ang)
{
	double	tmp[3];

	tmp[0] = vect[0];
	tmp[1] = vect[1];
	tmp[2] = vect[2];
	vect[0] = axe[0] * (cos(ang) + (tmp[0] * tmp[0]) * (1 - cos(ang))) +
		axe[1] * (tmp[0] * tmp[1] * (1 - cos(ang)) - tmp[2] * sin(ang)) +
		axe[2] * (tmp[0] * tmp[2] * (1 - cos(ang)) + tmp[1] * sin(ang));
	vect[1]= axe[0] * (tmp[1] * tmp[0] * (1 - cos(ang)) + tmp[2] * sin(ang)) +
		axe[1] * (cos(ang) + (tmp[1] * tmp[1]) * (1 - cos(ang))) +
		axe[2] * (tmp[1] * tmp[2] * (1 - cos(ang)) - tmp[0] * sin(ang));
	vect[2] = axe[0] * (tmp[2] * tmp[0] * (1 - cos(ang)) - tmp[1] * sin(ang)) +
		axe[1] * (tmp[2] * tmp[1] * (1 - cos(ang)) + tmp[0] * sin(ang)) +
		axe[2] * (cos(ang) + (tmp[2] * tmp[2]) * (1 - cos(ang)));
}
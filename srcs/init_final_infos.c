/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_final_infos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 17:16:53 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/22 15:06:02 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int		init_tab_3(double tab[3], int color[3], char *line)
{
	int	i;
	int	indice_tab;

	i = 0;
	indice_tab = 0;
	while (ft_isdigit(line[i]) == 0 && line[i] != '-' && line[i] != '\0')
		++i;
	while (indice_tab < 3 && line[i] != '\0')
	{
		if (tab != NULL)
			tab[indice_tab] = (double)atoi(&(line[i]));
		else
			color[indice_tab] = abs(atoi(&(line[i])));
		++indice_tab;
		while (line[i] != '\0' && (ft_isdigit(line[i]) == 1 || line[i] == '-'))
			++i;
		while (line[i] != '\0' && ft_isdigit(line[i]) == 0 && line[i] != '-')
			++i;
	}
	if (indice_tab < 3)
		return (-1);
	return (0);
}

int		init_3_values(double value[3], char *line, char *pattern)
{
	if (init_tab_3(value, NULL, line) == -1)
		return (-1);
	if (strstr(line, pattern) == NULL)
		return (-1);
	return (0);
}

int		init_colors(int color[3], char *line)
{
	if (init_tab_3(NULL, color, line) == -1)
		return (-1);
	convert_to_hex(color);
	if (strstr(line, "</color>") == NULL)
		return (-1);
	return (0);
}

int		init_one_value(double *value, char *line, char *pattern)
{
	int i;

	i = 0;
	while (ft_isdigit(line[i]) == 0 && line[i] != '-' && line[i] != '\0')
		++i;
	*value = (double)atoi(&(line[i]));
	if (strstr(line, pattern) == NULL)
		return (-1);
	return (0);
}

int		init_surface(SDL_Surface **texture, char *line)
{
	if ((*texture = SDL_LoadBMP(line)) == NULL)
		return (-1);
	return (0);
}

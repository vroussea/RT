/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_final_infos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 17:16:53 by eduwer            #+#    #+#             */
/*   Updated: 2017/04/12 18:40:34 by gboudrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <SDL_image.h>

bool	init_tab_3(double tab[3], int color[3], char *line)
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
			tab[indice_tab] = (double)ft_atoi(&(line[i]));
		else
			color[indice_tab] = abs(ft_atoi(&(line[i])));
		++indice_tab;
		while (line[i] != '\0' && (ft_isdigit(line[i]) == 1 || line[i] == '-'))
			++i;
		while (line[i] != '\0' && ft_isdigit(line[i]) == 0 && line[i] != '-')
			++i;
	}
	if (indice_tab < 3)
		return (true);
	return (false);
}

bool	init_3_values(double value[3], char *line, char *pattern)
{
	if (init_tab_3(value, NULL, line) == true)
		return (true);
	if (ft_strstr(line, pattern) == NULL)
		return (true);
	return (false);
}

bool	init_colors(int color[3], char *line)
{
	int i;

	i = 0;
	while (line[i] != '>')
		i++;
	if (init_tab_3(NULL, color, &(line[i])) == true)
		return (true);
	convert_to_hex(color);
	if (ft_strstr(line, "</color") == NULL)
		return (true);
	return (false);
}

bool	init_one_value(double *value, char *line, char *pattern)
{
	int i;

	i = 0;
	while (ft_isdigit(line[i]) == 0 && line[i] != '-' && line[i] != '\0')
		++i;
	*value = (double)ft_atoi(&(line[i]));
	if (ft_strstr(line, pattern) == NULL)
		return (true);
	return (false);
}

bool	init_surface(SDL_Surface **texture, char *line)
{
	char *buff;

	if ((*texture = IMG_Load(line)) == NULL)
	{
		buff = (char*)malloc(sizeof(char) * (23 + ft_strlen(line) + 1));
		sprintf(buff, "Cannot load texture : %s\n", line);
		write(1, buff, ft_strlen(buff));
		free(buff);
		exit(-1);
	}
	if (texture[0]->format->Amask == 0xff000000)
		convertsurface(*texture);
	return (false);
}

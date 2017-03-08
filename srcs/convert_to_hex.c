/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:38:01 by eduwer            #+#    #+#             */
/*   Updated: 2017/03/03 17:45:10 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rtv1.h>

int ft_abs(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

int		ft_hex(int nb)
{
	if (nb == 10)
		return (0xA);
	if (nb == 11)
		return (0xB);
	if (nb == 12)
		return (0xC);
	if (nb == 13)
		return (0xD);
	if (nb == 14)
		return (0xE);
	if (nb == 15)
		return (0xF);
	return (nb);
}

void	convert_to_hex(int tab[3])
{
	int	i;
	int	result;

	i = 0;
	while (i < 3)
	{
		tab[i] = ft_abs(tab[i]);
		if (tab[i] > 255)
			tab[i] = 255;
		result = 0x0;
		if (tab[i] >= 16)
		{
			result = 0x10 * ft_hex(tab[i] / 16);
			tab[i] %= 16;
		}
		result += ft_hex(tab[i]);
		tab[i] = result;
		i++;
	}
}

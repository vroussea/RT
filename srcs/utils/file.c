/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 08:47:47 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/07 08:47:48 by pfichepo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <rtv1.h>

static int			is_dir(const char *path)
{
	struct stat buf;

	stat(path, &buf);
	return (S_ISDIR(buf.st_mode));
}

void				checkread(char *s)
{
	int			fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		perror("CAN'T OPEN FILE ");
		exit(-1);
	}
	close(fd);
	if (is_dir(s))
	{
		perror("CANT OPEN FOLDER ");
		exit(-1);
	}
}

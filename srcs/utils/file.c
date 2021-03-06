/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfichepo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 08:47:47 by pfichepo          #+#    #+#             */
/*   Updated: 2017/03/16 16:18:53 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <rt.h>

#if defined(WIN32) || defined(WIN64)
# define S_ISREG(m) (((m) & S_IFMT) == S_IFREG)
# define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif

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

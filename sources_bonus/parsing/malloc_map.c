/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:20:27 by vihane            #+#    #+#             */
/*   Updated: 2025/07/17 16:29:07 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/*On ouvre le fichier, on lit la première ligne pour déterminer la taille
de la map, et on compte le nombre de lignes restantes pour déterminer
la hauteur de la map. n == On ignore les n premières lignes du fichier,
qui ne sont pas des lignes de carte. On calcule le nombre de lignes dans
la carte à partir de la n-ième ligne du fichier, et mettre ce nombre dans
cub3d->map_height*/
void	map_height_size(t_cub3d *cub3d, int fd, int n)
{
	char	*gnl_line;

	cub3d->map_height = 0;
	gnl_line = get_next_line(fd);
	if (!gnl_line)
		simple_exit(ERR_GNL);
	while (--n > 0)
	{
		free(gnl_line);
		gnl_line = get_next_line(fd);
	}
	while (gnl_line)
	{
		cub3d->map_height++;
		free(gnl_line);
		gnl_line = get_next_line(fd);
	}
	free(gnl_line);
	close(fd);
}

/*ajoute la ligne de la carte dans cub3d->map,
	et enregistre sa longueur dans width
et en retirant éventuellement le \n final.
n == On calcule l’indice du dernier caractère de line.
Ce sera utile pour vérifier s’il s’agit d’un \n*/
void	add_map_line(t_cub3d *cub3d, char *line)
{
	int	n;

	n = ft_strlen(line) - 1;
	cub3d->map[cub3d->map_height] = ft_strdup(line);
	if (!cub3d->map[cub3d->map_height])
		close_game(cub3d, ERR_STRDUP);
	if (cub3d->map[cub3d->map_height][n] == '\n')
		cub3d->map[cub3d->map_height][n] = '\0';
	cub3d->map_width[cub3d->map_height] = ft_strlen(cub3d->map
		[cub3d->map_height]);
	cub3d->map_height++;
	cub3d->map[cub3d->map_height] = NULL;
}

/*On ouvre le fichier, appelle map_size pour déterminer la taille (height)
de la map, on alloue ensuite la mémoire nécessaire pour le tableau
de ligne et leur largeur*/
void	init_map(t_cub3d *cub3d, char *file, int n)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		close_game(cub3d, ERR_FILE);
	map_height_size(cub3d, fd, n);
	cub3d->map = malloc(sizeof(char *) * (cub3d->map_height + 1));
	cub3d->map_width = malloc(sizeof(int) * (cub3d->map_height + 1));
	if (!cub3d->map || !cub3d->map_width)
	{
		close(fd);
		close_game(cub3d, ERR_MAP_INIT);
	}
	cub3d->map_height = 0;
	cub3d->map[0] = NULL;
}

/* Si cub3d->map est vide, on initialise la map avec init_map
Sinon, on ajoute la ligne courante à la map.
On ignore les espaces au début de la ligne et
on ensure que la ligne n'est pas vide.*/
void	keep_map(t_cub3d *cub3d, char *file, char *line, int n)
{
	int	i;

	i = 0;
	if (!cub3d->map)
		init_map(cub3d, file, n);
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
	{
		if (cub3d->map[0])
			close_game(cub3d, ERR_MAP);
		return ;
	}
	else if (line[i])
		add_map_line(cub3d, line);
}

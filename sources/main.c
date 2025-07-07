/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:04:36 by vihane            #+#    #+#             */
/*   Updated: 2025/07/07 15:04:24 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	simple_exit(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	exit(1);
}

int	main(int argc, char **argv)
{
	int		arg_len;
	int		fd;
	t_cub3d	cub3d;
	char	buffer[100];

	if (argc != 2)
		simple_exit(ERR_ARG);
	arg_len = ft_strlen(argv[1]);
	if (arg_len < 5 || ft_strncmp(argv[1] + arg_len - 4, ".cub", 4) != 0)
		close_game(&cub3d, ERR_CUB);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		simple_exit(ERR_FILE);
	if (read(fd, buffer, 100) == -1)
	{
		close(fd);
		simple_exit(ERR_FILE);
	}
	init_data(&cub3d);
	parse_map_first(&cub3d, argv[1]);
	init_mlx(&cub3d);
	init_game(&cub3d);
	return (0);
}

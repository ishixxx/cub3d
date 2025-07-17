/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:04:36 by vihane            #+#    #+#             */
/*   Updated: 2025/07/17 16:28:13 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	simple_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;
	int		arg_len;
	int		fd;
	char	buffer[130];

	if (argc != 2)
		simple_exit(ERR_ARG);
	arg_len = ft_strlen(argv[1]);
	if (arg_len < 5 || ft_strncmp(argv[1] + arg_len - 4, ".cub", 4) != 0)
		simple_exit(ERR_CUB);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		simple_exit(ERR_FILE);
	if (read(fd, buffer, 130) == -1)
	{
		close(fd);
		simple_exit(ERR_READ);
	}
	init_data(&cub3d);
	parse_map_first(&cub3d, argv[1]);
	init_mlx(&cub3d);
	init_game(&cub3d);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgalmich <vgalmich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:04:36 by vihane            #+#    #+#             */
/*   Updated: 2025/07/04 19:16:49 by vgalmich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// soit on garde cette fonction soit celle init_game dans gameplay
/*
void	handle_events(t_cub3d *cub3d)
{
	mlx_hook(cub3d->win_ptr, KEY_PRESS, 1L << 0, keypress, &cub3d);
	mlx_hook(cub3d->win_ptr, 3, 1L << 1, keyrelease, &cub3d);
	mlx_hook(cub3d->win_ptr, 17, 1L << 17, close_window, &cub3d);
	mlx_loop(cub3d->mlx_ptr);
}
*/

int	main(int argc, char **argv)
{
	int		arg_len;
//	int		fd;
	t_cub3d	cub3d;

	ft_memset(&cub3d, 0, sizeof(t_cub3d)); // memset au debut ?
	if (argc != 2)
		close_game(&cub3d, ERR_ARG);
	arg_len = ft_strlen(argv[1]);
	if (arg_len < 5 || ft_strncmp(argv[1] + arg_len - 4, ".cub", 4) != 0)
		close_game(&cub3d, ERR_CUB);
	// fd = open(argv[1], O_RDONLY);
	// if (fd == -1)
	//	close_game(&cub3d, ERR_FILE);
	cub3d.mlx_ptr = mlx_init();
	if (!cub3d.mlx_ptr)
		close_game(&cub3d, "Failed to initialize mlx");
	init_mlx(&cub3d);
	if (!parse_map_first(-1, &cub3d, argv[1]))
	{
		printf("parse_map_first a echoue\n");
	//	close(fd);
		close_game(&cub3d, ERR_MAP);
	}
	if (init_file(argv[1], &cub3d) != 0)
		return (1);
	init_data(&cub3d);
	init_player(&cub3d);
	// handle_events(&cub3d);
	init_game(&cub3d);
	return (0);
}

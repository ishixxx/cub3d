/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:04:36 by vihane            #+#    #+#             */
/*   Updated: 2025/06/10 15:34:59 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    t_cub3d *cub3d;
    int     arg_len;
    
    if(argc != 2)
        return(ft_putstr_fd(ERR_ARG, 2), 1);
    arg_len = ft_strlen(argv[1]);
    data_init(argc, argv, &cub3d);
    if(arg_len < 5 || ft_strncmp(argv[1] + arg_len - 4, ".cub", 4) != 0)
        return(ft_putstr_fd(ERR_CUB, 2), 1);
    if (!cub3d->mlx_ptr)
        return(ft_putstr_fd(ERR_MLX, 2), 1);
}
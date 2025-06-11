/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vihane <vihane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:04:36 by vihane            #+#    #+#             */
/*   Updated: 2025/06/11 22:25:03 by vihane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int main(int argc, char **argv)
{
    t_cub3d *cub3d;
    int     arg_len;
    
    if(argc != 2)
        return(ft_putstr_fd(ERR_ARG, 2), 1);
    arg_len = ft_strlen(argv[1]);
    if(arg_len < 5 || ft_strncmp(argv[1] + arg_len - 4, ".cub", 4) != 0)
    return(ft_putstr_fd(ERR_CUB, 2), 1);
    cub3d = malloc(sizeof(t_cub3d));
    if (!cub3d)
    return(ft_putstr_fd(ERR_MALLOC, 2), 1);
    data_init(argc, argv, cub3d);
    return (0);
}
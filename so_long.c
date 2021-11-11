/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 13:27:34 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/11 18:37:56 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "so_long.h"
#include "minilibx_mms_20200219/mlx.h"

int	main(int argc, char **argv)
{
	t_game	g;

	init_g(&g);
	if (argc == 2 && is_valid_map(argv[1], &g.map))
	{
		g.mlx = mlx_init();
		g.win = mlx_new_window(g.mlx, g.map.cols * g.map.px, \
				g.map.rows * g.map.px, "so_long - hbaddrul");
		init_lines_and_images(argv[1], &g);
		put_images(&g);
		mlx_key_hook(g.win, key_hook, &g);
		mlx_loop(g.mlx);
	}
	else
		printf("Error\n");
	return (0);
}

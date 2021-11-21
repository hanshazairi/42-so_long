/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 13:27:34 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/21 18:33:44 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "so_long.h"
#include "minilibx_opengl_20191021/mlx.h"
#include "libft/libft.h"

static int	red_circle_pressed(t_game *g)
{
	end_game(g);
	return (0);
}

static int	key_hook(int keycode, t_game *g)
{
	if (keycode == ESC)
		end_game(g);
	else if (keycode == LEFT || keycode == RIGHT || keycode == DOWN \
			|| keycode == UP)
	{
		if (keycode == LEFT)
			g->player.attempt.x = g->player.actual.x - 1;
		else if (keycode == RIGHT)
			g->player.attempt.x = g->player.actual.x + 1;
		else if (keycode == DOWN)
			g->player.attempt.y = g->player.actual.y + 1;
		else if (keycode == UP)
			g->player.attempt.y = g->player.actual.y - 1;
		if (g->lines[g->player.attempt.y][g->player.attempt.x] != '1')
			move(g);
		else
		{
			g->player.attempt.x = g->player.actual.x;
			g->player.attempt.y = g->player.actual.y;
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char	*moves;
	t_game	g;

	init_g(&g);
	if (argc == 2 && is_valid_map(argv[1], &g.map))
	{
		g.mlx = mlx_init();
		g.win = mlx_new_window(g.mlx, g.map.cols * g.map.px, \
				g.map.rows * g.map.px, "so_long - hbaddrul");
		init_lines_and_images(argv[1], &g);
		init_enemies(&g);
		put_images(&g);
		moves = ft_itoa(g.player.moves);
		mlx_string_put(g.mlx, g.win, 12, 22, 0x00FFFFFF, moves);
		free(moves);
		mlx_hook(g.win, 17, 0, red_circle_pressed, &g);
		mlx_key_hook(g.win, key_hook, &g);
		mlx_loop(g.mlx);
	}
	else
		ft_putendl_fd("Error", 2);
	return (0);
}

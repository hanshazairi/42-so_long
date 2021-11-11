/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:21:41 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/11 20:54:30 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "so_long.h"
#include "minilibx_mms_20200219/mlx.h"

void	end_game(t_game *g)
{
	char	**tmp;

	if (g->player.c == g->map.c)
		printf("You win!\n");
	else
		printf("You lose!\n");
	tmp = g->lines;
	while (*tmp)
		free(*tmp++);
	free(g->lines);
	mlx_destroy_image(g->mlx, g->o);
	mlx_destroy_image(g->mlx, g->c);
	mlx_destroy_image(g->mlx, g->e);
	mlx_destroy_image(g->mlx, g->p);
	mlx_clear_window(g->mlx, g->win);
	mlx_destroy_window(g->mlx, g->win);
	exit(0);
}

void	move(t_game *g)
{
	const int	attempt_x = g->player.attempt.x;
	const int	attempt_y = g->player.attempt.y;
	const int	actual_x = g->player.actual.x;
	const int	actual_y = g->player.actual.y;

	if (g->lines[attempt_y][attempt_x] == '1')
	{
		g->player.attempt.x = actual_x;
		g->player.attempt.y = actual_y;
	}
	else
	{
		if (g->lines[g->player.attempt.y][g->player.attempt.x] == 'C')
			g->player.c += 1;
		else if (g->lines[g->player.attempt.y][g->player.attempt.x] == 'E')
			end_game(g);
		g->lines[g->player.actual.y][g->player.actual.x] = '0';
		g->lines[g->player.attempt.y][g->player.attempt.x] = 'P';
		mlx_clear_window(g->mlx, g->win);
		put_images(g);
		g->player.moves += 1;
		printf("%d\n", g->player.moves);
	}
}

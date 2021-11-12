/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:21:41 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/12 20:01:35 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "so_long.h"
#include "minilibx_mms_20200219/mlx.h"

void	end_game(t_game *g)
{
	char	**tmp;

	if (g->lines[g->player.attempt.y][g->player.attempt.x] == 'E' \
			&& g->player.c == g->map.c)
		printf("You win!\n");
	else
		printf("You lose!\n");
	tmp = g->lines;
	while (*tmp)
		free(*tmp++);
	free(g->lines);
	if (g->enemies)
		free(g->enemies);
	mlx_destroy_image(g->mlx, g->o);
	mlx_destroy_image(g->mlx, g->c);
	mlx_destroy_image(g->mlx, g->e);
	mlx_destroy_image(g->mlx, g->p);
	mlx_destroy_image(g->mlx, g->v);
	mlx_clear_window(g->mlx, g->win);
	mlx_destroy_window(g->mlx, g->win);
	free(g->mlx);
	exit(0);
}

void	move_enemies(t_game *g)
{
	int			k;
	t_player	enemy;

	k = -1;
	while (++k < g->map.v)
	{
		enemy = g->enemies[k];
		if (g->lines[enemy.actual.y - 1][enemy.actual.x] != '1' \
				&& g->lines[enemy.actual.y - 1][enemy.actual.x] != 'C')
			g->lines[enemy.actual.y - 1][enemy.actual.x] = 'V';
		else
			g->lines[enemy.actual.y + 1][enemy.actual.x] = 'V';
		g->lines[enemy.actual.y][enemy.actual.x] = '0';
	}
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
		g->lines[g->player.actual.y][g->player.actual.x] = '0';
		move_enemies(g);
		if (g->lines[g->player.attempt.y][g->player.attempt.x] == 'C')
			g->player.c += 1;
		else if (g->lines[g->player.attempt.y][g->player.attempt.x] == 'E' \
				|| g->lines[g->player.attempt.y][g->player.attempt.x] == 'V')
			end_game(g);
		g->lines[g->player.attempt.y][g->player.attempt.x] = 'P';
		g->player.moves += 1;
		mlx_clear_window(g->mlx, g->win);
		put_images(g);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:21:41 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/21 15:23:38 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "so_long.h"
#include "minilibx_opengl_20191021/mlx.h"
#include "libft/libft.h"

static void	move_e(t_game *g)
{
	int		k;
	t_enemy	enemy;

	k = -1;
	while (++k < g->map.v)
	{
		enemy = g->enemies[k];
		if (g->lines[enemy.actual.y - 1][enemy.actual.x] == '0' )
			g->lines[enemy.actual.y - 1][enemy.actual.x] = 'V';
		else if (g->lines[enemy.actual.y + 1][enemy.actual.x] == '0')
			g->lines[enemy.actual.y + 1][enemy.actual.x] = 'V';
		else
			continue ;
		g->lines[enemy.actual.y][enemy.actual.x] = '0';
	}
}

static void	animate(t_game *g)
{
	void	*tmp;

	tmp = g->c;
	g->c = g->c2;
	g->c2 = tmp;
	if (g->lines[g->player.attempt.y][g->player.attempt.x] == 'C')
		g->p = g->p3;
	else
		g->p = g->p2;
}

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
	mlx_destroy_image(g->mlx, g->c2);
	mlx_destroy_image(g->mlx, g->e);
	mlx_destroy_image(g->mlx, g->p2);
	mlx_destroy_image(g->mlx, g->p3);
	mlx_destroy_image(g->mlx, g->v);
	mlx_clear_window(g->mlx, g->win);
	mlx_destroy_window(g->mlx, g->win);
	free(g->mlx);
	exit(0);
}

void	move(t_game *g)
{
	char	*moves;

	if (g->lines[g->player.attempt.y][g->player.attempt.x] == 'V')
		end_game(g);
	g->lines[g->player.actual.y][g->player.actual.x] = '0';
	move_e(g);
	animate(g);
	if (g->lines[g->player.attempt.y][g->player.attempt.x] == 'C')
		g->player.c += 1;
	else if (g->lines[g->player.attempt.y][g->player.attempt.x] == 'E' \
			|| g->lines[g->player.attempt.y][g->player.attempt.x] == 'V')
		end_game(g);
	g->lines[g->player.attempt.y][g->player.attempt.x] = 'P';
	g->player.moves += 1;
	mlx_clear_window(g->mlx, g->win);
	put_images(g);
	moves = ft_itoa(g->player.moves);
	mlx_string_put(g->mlx, g->win, 12, 22, 0xFFFFFFFF, moves);
	free(moves);
}

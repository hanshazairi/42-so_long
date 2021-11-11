/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:30:11 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/11 20:57:13 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "so_long.h"
#include "minilibx_mms_20200219/mlx.h"

static void	update_player(t_game *g, int i, int j)
{
	g->player.attempt.x = j;
	g->player.attempt.y = i;
	g->player.actual.x = j;
	g->player.actual.y = i;
}

void	init_g(t_game *g)
{
	g->player.c = 0;
	g->player.moves = 0;
	g->map.c = 0;
	g->map.e = 0;
	g->map.p = 0;
	g->map.diff_cols = 0;
	g->map.px = 16;
}

void	init_lines_and_images(char *file, t_game *g)
{
	int			i;
	char		*line;
	char		**ret;
	const int	fd = open(file, O_RDONLY);

	ret = malloc(sizeof(char *) * (g->map.rows + 1));
	if (!ret)
		return ;
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		ret[i++] = line;
		line = get_next_line(fd);
	}
	ret[i] = 0;
	g->lines = ret;
	g->o = mlx_png_file_to_image(g->mlx, "sprites/o.png", &g->map.px, \
		&g->map.px);
	g->c = mlx_png_file_to_image(g->mlx, "sprites/c.png", &g->map.px, \
			&g->map.px);
	g->e = mlx_png_file_to_image(g->mlx, "sprites/e.png", &g->map.px, \
			&g->map.px);
	g->p = mlx_png_file_to_image(g->mlx, "sprites/p.png", &g->map.px, \
			&g->map.px);
}

void	put_images(t_game *g)
{
	int	i;
	int	j;
	int	(*f)(void *, void *, void *, int x, int y);

	f = mlx_put_image_to_window;
	i = 0;
	while (i < g->map.rows)
	{
		j = 0;
		while (j < g->map.cols)
		{
			if (g->lines[i][j] == '1')
				f(g->mlx, g->win, g->o, j * g->map.px, i * g->map.px);
			else if (g->lines[i][j] == 'C')
				f(g->mlx, g->win, g->c, j * g->map.px, i * g->map.px);
			else if (g->lines[i][j] == 'E')
				f(g->mlx, g->win, g->e, j * g->map.px, i * g->map.px);
			else if (g->lines[i][j] == 'P')
				f(g->mlx, g->win, g->p, j * g->map.px, i * g->map.px);
			if (g->lines[i][j] == 'P')
				update_player(g, i, j);
			++j;
		}
		++i;
	}
}

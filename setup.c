/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:30:11 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/13 01:13:40 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "so_long.h"
#include "minilibx_mms_20200219/mlx.h"
#include "libft/libft.h"

static int	update_player(t_game *g, int i, int j)
{
	g->player.attempt.x = j;
	g->player.attempt.y = i;
	g->player.actual.x = j;
	g->player.actual.y = i;
	return (1);
}

static int	update_enemies(t_game *g, int i, int j, int k)
{
	g->enemies[k].attempt.x = j;
	g->enemies[k].attempt.y = i;
	g->enemies[k].actual.x = j;
	g->enemies[k].actual.y = i;
	return (1);
}

void	init_g(t_game *g)
{
	g->player.c = 0;
	g->player.moves = 0;
	g->map.c = 0;
	g->map.e = 0;
	g->map.p = 0;
	g->map.v = 0;
	g->map.diff_cols = 0;
	g->map.px = 32;
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
	g->o = mlx_png_file_to_image(g->mlx, "png/o.png", &g->map.px, &g->map.px);
	g->c = mlx_png_file_to_image(g->mlx, "png/c.png", &g->map.px, &g->map.px);
	g->e = mlx_png_file_to_image(g->mlx, "png/e.png", &g->map.px, &g->map.px);
	g->p = mlx_png_file_to_image(g->mlx, "png/p.png", &g->map.px, &g->map.px);
	g->v = mlx_png_file_to_image(g->mlx, "png/v.png", &g->map.px, &g->map.px);
}

void	init_enemies(t_game *g)
{
	int			k;
	t_player	*enemies;

	enemies = malloc(sizeof(t_player) * g->map.v);
	if (!enemies)
		return ;
	k = -1;
	g->enemies = enemies;
}

void	put_images(t_game *g)
{
	int			i;
	int			j;
	int			k;
	int			(*f)(void *, void *, void *, int x, int y);
	const char	*str = ft_itoa(g->player.moves);

	f = mlx_put_image_to_window;
	i = -1;
	k = -1;
	while (++i < g->map.rows)
	{
		j = -1;
		while (++j < g->map.cols)
		{
			if (g->lines[i][j] == '1')
				f(g->mlx, g->win, g->o, j * g->map.px, i * g->map.px);
			else if (g->lines[i][j] == 'C')
				f(g->mlx, g->win, g->c, j * g->map.px, i * g->map.px);
			else if (g->lines[i][j] == 'E')
				f(g->mlx, g->win, g->e, j * g->map.px, i * g->map.px);
			else if (g->lines[i][j] == 'P' && update_player(g, i, j))
				f(g->mlx, g->win, g->p, j * g->map.px, i * g->map.px);
			else if (g->lines[i][j] == 'V' && update_enemies(g, i, j, ++k))
				f(g->mlx, g->win, g->v, j * g->map.px, i * g->map.px);
		}
	}
	mlx_string_put(g->mlx, g->win, 12, 22, 16777215, (char *)str);
	free((char *)str);
}

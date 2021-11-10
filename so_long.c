/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 13:27:34 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/10 18:08:50 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "so_long.h"
#include "minilibx_mms_20200219/mlx.h"
#include "libft/libft.h"

char	**init_lines(char *file, t_map *map)
{
	int			i;
	char		*line;
	char		**ret;
	const int	fd = open(file, O_RDONLY);

	ret = malloc(sizeof(char *) * (map->rows + 1));
	if (!ret)
		return (0);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		ret[i++] = line;
		line = get_next_line(fd);
	}
	ret[i] = 0;
	return (ret);
}

void	init_images(t_game *g)
{
	g->o = mlx_png_file_to_image(g->mlx, "sprites/o.png", &g->map.tile_size, \
			&g->map.tile_size);
	g->c = mlx_png_file_to_image(g->mlx, "sprites/c.png", &g->map.tile_size, \
			&g->map.tile_size);
	g->e = mlx_png_file_to_image(g->mlx, "sprites/e.png", &g->map.tile_size, \
			&g->map.tile_size);
	g->p = mlx_png_file_to_image(g->mlx, "sprites/p.png", &g->map.tile_size, \
			&g->map.tile_size);
}

void	put_images(t_game *g)
{
	int	i;
	int	j;

	i = 0;
	while (i < g->map.rows)
	{
		j = 0;
		while (j < g->map.cols)
		{
			if (g->lines[i][j] == '1')
				mlx_put_image_to_window(g->mlx, g->win, g->o, \
						j * g->map.tile_size, i * g->map.tile_size);
			else if (g->lines[i][j] == 'C')
				mlx_put_image_to_window(g->mlx, g->win, g->c, \
						j * g->map.tile_size, i * g->map.tile_size);
			else if (g->lines[i][j] == 'E')
				mlx_put_image_to_window(g->mlx, g->win, g->e, \
						j * g->map.tile_size, i * g->map.tile_size);
			else if (g->lines[i][j] == 'P')
				mlx_put_image_to_window(g->mlx, g->win, g->p, \
						j * g->map.tile_size, i * g->map.tile_size);
			++j;
		}
		++i;
	}
}

int	key_hook(int keycode, void *param)
{
	(void)param;
	ft_putnbr_fd(keycode, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	g;

	g.map.tile_size = 16;
	g.map.c = 0;
	g.map.e = 0;
	g.map.p = 0;
	g.map.diff_cols = 0;
	if (argc == 2 && is_valid_map(argv[1], &g.map))
	{
		g.lines = init_lines(argv[1], &g.map);
		g.mlx = mlx_init();
		g.win = mlx_new_window(g.mlx, g.map.cols * g.map.tile_size, \
				g.map.rows * g.map.tile_size, "so_long - hbaddrul");
		init_images(&g);
		put_images(&g);
		mlx_key_hook(g.win, key_hook, (void *)0);
		mlx_loop(g.mlx);
	}
	else
		ft_putendl_fd("Error", 2);
	return (0);
}

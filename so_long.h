/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:53:16 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/10 17:56:37 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# define BUFFER_SIZE 42

typedef struct s_map
{
	int		rows;
	int		cols;
	int		c;
	int		e;
	int		p;
	int		diff_cols;
	int		tile_size;
	char	**lines;
}	t_map;

typedef struct s_game
{
	char	**lines;
	void	*o;
	void	*c;
	void	*e;
	void	*p;
	void	*mlx;
	void	*win;
	t_map	map;
}	t_game;

/* get_next_line.c */
char	*get_next_line(int fd);

/* validate.c */
int		is_valid_map(char *file, t_map *map);

#endif

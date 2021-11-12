/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbaddrul <hbaddrul@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:53:16 by hbaddrul          #+#    #+#             */
/*   Updated: 2021/11/12 19:33:19 by hbaddrul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# define BUFFER_SIZE 42
# define ESC 53
# define LEFT 0
# define RIGHT 2
# define DOWN 1
# define UP 13

typedef struct s_xy
{
	int	x;
	int	y;
}	t_xy;

typedef struct s_player
{
	int		c;
	int		moves;
	t_xy	attempt;
	t_xy	actual;
}	t_player;

typedef struct s_map
{
	int		rows;
	int		cols;
	int		c;
	int		e;
	int		p;
	int		v;
	int		diff_cols;
	int		px;
	char	**lines;
}	t_map;

typedef struct s_game
{
	char		**lines;
	void		*o;
	void		*c;
	void		*e;
	void		*p;
	void		*v;
	void		*mlx;
	void		*win;
	t_player	player;
	t_player	*enemies;
	t_map		map;
}	t_game;

/* get_next_line.c */
char	*get_next_line(int fd);

/* validate.c */
int		is_valid_map(char *file, t_map *map);

/* setup.c */
void	init_g(t_game *g);
void	init_lines_and_images(char *file, t_game *g);
void	init_enemies(t_game *g);
void	put_images(t_game *g);

/* gameplay.c */
void	end_game(t_game *g);
void	move(t_game *g);

#endif
